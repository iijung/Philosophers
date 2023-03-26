/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:01:16 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/27 03:49:28 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	_finally(
	struct s_common *common,
	struct s_locker *forks)
{
	long	i;

	pthread_mutex_unlock(&common->lock);
	pthread_mutex_destroy(&common->lock);
	i = 0;
	while (i < common->number_of_philosophers)
	{
		pthread_mutex_unlock(&forks[i].key);
		pthread_mutex_destroy(&forks[i].key);
		++i;
	}
}

static int	_initial(
	struct s_common *common,
	struct s_locker *forks,
	struct s_philosopher *philos)
{
	int						i;
	int						num_of_philos;
	struct s_philosopher	*philo;

	if (pthread_mutex_init(&common->lock, NULL) == -1)
		return (-1);
	num_of_philos = common->number_of_philosophers;
	i = -1;
	while (++i < num_of_philos)
		if (pthread_mutex_init(&forks[i].key, NULL) == -1)
			return (-1);
	i = -1;
	while (++i < num_of_philos)
	{
		philo = &philos[i];
		philo->thread_num = i + 1;
		philo->forks[i % 2] = &forks[i];
		philo->forks[!(i % 2)] = &forks[(i + 1) % num_of_philos];
	}
	return (EXIT_SUCCESS);
}

static int	_execute(
	struct s_common *common,
	struct s_philosopher *philos)
{
	int						i;
	int						ret;
	struct s_philosopher	*philo;

	i = 0;
	ret = EXIT_SUCCESS;
	if (pthread_mutex_lock(&common->lock) == 0)
	{
		while (i < common->number_of_philosophers)
		{
			philo = &philos[i];
			if (pthread_create(&philo->thread_id, NULL, philo_do, philo) < 0)
			{
				ret = EXIT_FAILURE;
				break ;
			}
			++i;
		}
		gettimeofday(&common->start_time, NULL);
		pthread_mutex_unlock(&common->lock);
	}
	while (i > 0)
		pthread_join(philos[--i].thread_id, NULL);
	return (ret);
}

static int	simulate(struct s_common *common)
{
	int						ret;
	const int				num_of_philos = common->number_of_philosophers;
	struct s_philosopher	*philos;
	struct s_locker			*forks;

	ret = EXIT_FAILURE;
	forks = ft_calloc(num_of_philos, sizeof(struct s_locker));
	philos = ft_calloc(num_of_philos, sizeof(struct s_philosopher));
	if (forks && philos)
	{
		ret = _initial(common, forks, philos);
		if (ret == EXIT_SUCCESS)
			ret = _execute(common, philos);
		_finally(common, forks);
	}
	(free(forks), free(philos));
	return (ret);
}

int	main(int argc, char *argv[])
{
	struct s_common	common;

	memset(&common, 0, sizeof(struct s_common));
	if (argv == NULL || (argc != 5 && argc != 6))
		return (-1);
	common.number_of_philosophers = ft_atol(argv[1]);
	common.time_to_die = ft_atol(argv[2]);
	common.time_to_eat = ft_atol(argv[3]);
	common.time_to_sleep = ft_atol(argv[4]);
	common.number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		common.number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
	if (errno)
	{
		ft_putstr_fd("Usage: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(
			" number_of_philosophers"
			" time_to_die time_to_eat time_to_sleep"
			" [number_of_times_each_philosophers_must_eat]\n", STDERR_FILENO);
		return (-1);
	}
	return (simulate(&common));
}
