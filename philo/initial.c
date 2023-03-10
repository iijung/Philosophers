/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:21:25 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/11 01:12:50 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	p_atoi(const char *str, int *num)
{
	if (str == NULL || num == NULL)
		return (-1);
	*num = 0;
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (-1);
		else if (*num > INT_MAX / 10 || (*num == INT_MAX / 10 && *str > '7'))
			return (-1);
		else
			*num = *num * 10 + *str++ - '0';
	}
	return (0);
}

static int	parse(struct s_common *common, int argc, char *argv[])
{
	if (argv == NULL
		|| (argc != 5 && argc != 6)
		|| p_atoi(argv[1], &common->number_of_philosophers)
		|| p_atoi(argv[2], &common->time_to_die)
		|| p_atoi(argv[3], &common->time_to_eat)
		|| p_atoi(argv[4], &common->time_to_sleep))
		return (-1);
	common->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6
		&& p_atoi(argv[5], &common->number_of_times_each_philosopher_must_eat))
		return (-1);
	return (0);
}

static int	init(struct s_simulator *simulator)
{
	int						i;
	int						num_of_philos;
	struct s_philosopher	*philo;

	if (pthread_mutex_init(&simulator->common.lock, NULL) == -1)
		return (-1);
	num_of_philos = simulator->common.number_of_philosophers;
	i = -1;
	while (++i < num_of_philos)
		if (pthread_mutex_init(&simulator->forks[i].lock, NULL) == -1)
			return (-1);
	i = -1;
	while (++i < num_of_philos)
	{
		philo = &simulator->philos[i];
		philo->thread_num = i + 1;
		philo->common = &simulator->common;
		philo->forks[i % 2] = &simulator->forks[i];
		philo->forks[!(i % 2)] = &simulator->forks[(i + 1) % num_of_philos];
	}
	return (0);
}

extern void	finally(struct s_simulator *simulator)
{
	int	i;

	pthread_mutex_destroy(&simulator->common.lock);
	i = -1;
	while (++i < simulator->common.number_of_philosophers)
		pthread_mutex_destroy(&simulator->forks[i].lock);
	free(simulator->forks);
	free(simulator->philos);
}

extern int	initial(struct s_simulator *simulator, int argc, char *argv[])
{
	int	num;

	if (parse(&simulator->common, argc, argv))
	{
		printf("Usage: %s"
			" number_of_philosophers time_to_die time_to_eat time_to_sleep"
			" [number_of_times_each_philosophers_must_eat]\n", argv[0]);
		return (-1);
	}
	num = simulator->common.number_of_philosophers;
	simulator->forks = ft_calloc(num, sizeof(struct s_fork));
	simulator->philos = ft_calloc(num, sizeof(struct s_philosopher));
	while (1)
	{
		if (simulator->forks == NULL || simulator->philos == NULL)
			break ;
		if (init(simulator) < 0)
			break ;
		return (0);
	}
	finally(simulator);
	return (-1);
}
