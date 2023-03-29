/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:30:19 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/29 16:08:19 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulate_bonus.h"
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

static void	_finally(struct s_simulator *simulator)
{
	struct s_common *const		common = simulator->common;

	sem_close(common->lock);
	sem_unlink("common");
}

static int	_initial(struct s_simulator *simulator)
{
	struct s_common *const		common = simulator->common;
	struct s_philosopher *const	philos = simulator->philos;
	t_fork *const				forks = simulator->forks;
	long						i;

	sem_unlink("common");
	common->lock = sem_open("common", O_CREAT | O_EXCL, 0644, 1);
	if (common->lock == SEM_FAILED)
		return (PHILO_ERROR);
	i = 1;
	while (i <= common->number_of_philosophers)
	{
		philos[i - 1].num = i;
		philos[i - 1].common = common;
		philos[i - 1].forks = forks;
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
		if (fork() == 0)
			exit(philo_do(&philos[i]));
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < common->number_of_philosophers)
	{
		if (fork() == 0)
			exit(philo_do(&philos[i]));
		i += 2;
	}
	return (PHILO_INPROGRESS);
}

static int	_stop(struct s_simulator *simulator, int exit_status)
{
	struct s_common *const		common = simulator->common;
	long						i;
	int							status;

	i = 0;
	while (i < common->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
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
		simulator.forks = create_fork(num);
		if (simulator.forks != SEM_FAILED)
		{
			ret = _initial(&simulator);
			if (ret == PHILO_INPROGRESS)
				ret = _stop(&simulator, _start(&simulator));
			_finally(&simulator);
		}
		destroy_fork(simulator.forks);
	}
	free(simulator.philos);
	return (ret);
}
