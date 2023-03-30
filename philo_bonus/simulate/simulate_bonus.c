/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:30:19 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/29 19:08:30 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulate_bonus.h"
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

static void	_finally(struct s_simulator *simulator)
{
	struct s_common *const		common = simulator->common;

	destroy_share(SHARE_COMMON, common->lock);
	destroy_share(SHARE_COUNTER, common->counter);
	destroy_share(SHARE_FORK, simulator->forks);
}

static int	_initial(struct s_simulator *simulator)
{
	struct s_common *const		common = simulator->common;
	struct s_philosopher *const	philos = simulator->philos;
	const long					num = common->number_of_philosophers;
	long						i;

	common->lock = create_share(SHARE_COMMON, 1);
	common->counter = create_share(SHARE_COUNTER, num);
	simulator->forks = create_share(SHARE_FORK, num);
	if (common->lock == SEM_FAILED
		|| common->counter == SEM_FAILED
		|| simulator->forks == SEM_FAILED)
		return (PHILO_ERROR);
	i = 1;
	while (i <= common->number_of_philosophers)
	{
		philos[i - 1].num = i;
		philos[i - 1].common = common;
		philos[i - 1].forks = simulator->forks;
		++i;
	}
	return (PHILO_INPROGRESS);
}

static int	_start(struct s_simulator *simulator)
{
	struct s_common *const		common = simulator->common;
	struct s_philosopher *const	philos = simulator->philos;
	long						i;

	i = 0;
	gettimeofday(&common->start_time, NULL);
	while (i < common->number_of_philosophers)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
			exit(philo_do(&philos[i]));
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < common->number_of_philosophers)
	{
		philos[i].pid = fork();
		if (philos[i].pid == 0)
			exit(philo_do(&philos[i]));
		i += 2;
	}
	return (PHILO_INPROGRESS);
}

static int	_stop(struct s_simulator *simulator, int exit_status)
{
	struct s_common *const		common = simulator->common;
	struct s_philosopher *const	philos = simulator->philos;
	long						i;

	usleep(1000);
	i = 0;
	while (i < common->number_of_philosophers)
	{
		get_share(common->counter);
		++i;
	}
	i = 0;
	while (i < common->number_of_philosophers)
	{
		if (waitpid(philos[i].pid, NULL, WNOHANG) == 0)
			kill(philos[i].pid, SIGINT);
		++i;
	}
	return (exit_status);
}

int	simulate(struct s_common *common)
{
	struct s_simulator	simulator;
	const long			num = common->number_of_philosophers;
	int					ret;

	ret = PHILO_ERROR;
	simulator.common = common;
	simulator.philos = malloc(sizeof(struct s_philosopher) * num);
	if (simulator.philos)
	{
		memset(simulator.philos, 0, sizeof(struct s_philosopher) * num);
		ret = _initial(&simulator);
		if (ret == PHILO_INPROGRESS)
			ret = _stop(&simulator, _start(&simulator));
		_finally(&simulator);
	}
	free(simulator.philos);
	return (ret);
}
