/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:30:19 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 23:48:12 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulate.h"
#include <stdlib.h>
#include <string.h>

static void	_finally(struct s_simulator *simulator)
{
	struct s_common *const		common = simulator->common;
	t_fork *const				forks = simulator->forks;
	long						i;

	pthread_mutex_destroy(&common->lock);
	i = 0;
	while (i < common->number_of_philosophers)
		destroy_fork(&forks[i++]);
}

static int	_initial(struct s_simulator *simulator)
{
	struct s_common *const		common = simulator->common;
	struct s_philosopher *const	philos = simulator->philos;
	t_fork *const				forks = simulator->forks;
	long						i;

	if (pthread_mutex_init(&common->lock, NULL) == -1)
		return (PHILO_ERROR);
	i = 1;
	while (i <= common->number_of_philosophers)
	{
		if (create_fork(&forks[i - 1]) == -1)
			return (PHILO_ERROR);
		philos[i - 1].num = i;
		philos[i - 1].common = common;
		philos[i - 1].forks[0] = &forks[i - 1];
		philos[i % common->number_of_philosophers].forks[1] = &forks[i - 1];
		++i;
	}
	return (PHILO_INPROGRESS);
}

static int	_start(struct s_simulator *simulator)
{
	struct s_common *const		common = simulator->common;
	struct s_philosopher *const	philos = simulator->philos;
	long						i;
	int							ret;

	i = 0;
	ret = PHILO_INPROGRESS;
	gettimeofday(&common->start_time, NULL);
	while (i < common->number_of_philosophers && ret == PHILO_INPROGRESS)
	{
		ret = pthread_create(&philos[i].tid, NULL, philo_do, &philos[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < common->number_of_philosophers && ret == PHILO_INPROGRESS)
	{
		ret = pthread_create(&philos[i].tid, NULL, philo_do, &philos[i]);
		i += 2;
	}
	return (ret);
}

static int	_stop(struct s_simulator *simulator, int exit_status)
{
	struct s_common *const		common = simulator->common;
	struct s_philosopher *const	philos = simulator->philos;
	long						i;

	if (exit_status == PHILO_ERROR)
	{
		pthread_mutex_lock(&common->lock);
		common->should_terminate = 1;
		pthread_mutex_unlock(&common->lock);
	}
	i = 0;
	while (i < common->number_of_philosophers)
		pthread_join(philos[i++].tid, NULL);
	return (exit_status);
}

int	simulate(struct s_common *common)
{
	struct s_simulator	simulator;
	const long			num = common->number_of_philosophers;
	int					ret;

	ret = PHILO_ERROR;
	simulator.common = common;
	simulator.forks = malloc(sizeof(t_fork) * num);
	simulator.philos = malloc(sizeof(struct s_philosopher) * num);
	if (simulator.forks && simulator.philos)
	{
		memset(simulator.forks, 0, sizeof(t_fork) * num);
		memset(simulator.philos, 0, sizeof(struct s_philosopher) * num);
		ret = _initial(&simulator);
		if (ret == PHILO_INPROGRESS)
			ret = _stop(&simulator, _start(&simulator));
		_finally(&simulator);
	}
	free(simulator.forks);
	free(simulator.philos);
	return (ret);
}