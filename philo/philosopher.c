/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:33:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/08 01:28:30 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_speak(struct s_philosopher *philo, const char *status)
{
	struct timeval	*start_time;

	start_time = &philo->common->start_time;
	pthread_mutex_lock(&philo->common->lock);
	printf("%d\t%d%s", now(start_time), philo->thread_num, status);
	pthread_mutex_unlock(&philo->common->lock);
}

static int	philo_sleep(struct s_philosopher *philo)
{
	int			curr_time;

	philo_speak(philo, STATUS_SLEEP);
	curr_time = now(&philo->ate_time);
	while (curr_time < philo->common->time_to_die)
	{
		if (philo->common->done == 1)
			return (EXIT_FAILURE);
		if (curr_time >= philo->common->time_to_sleep)
			return (0);
		usleep(100);
		curr_time = now(&philo->ate_time);
	}
	philo->is_died = 1;
	return (EXIT_FAILURE);
}

static int	get_fork(struct s_philosopher *philo, int is_right)
{
	int			success;
	int			curr_time;

	if (philo->is_died)
		return (EXIT_FAILURE);
	success = 0;
	curr_time = now(&philo->ate_time);
	while (curr_time < philo->common->time_to_die)
	{
		if (is_right == 0 || philo->forks[0] != philo->forks[1])
		{
			pthread_mutex_lock(&philo->forks[is_right]->lock);
			if (philo->forks[is_right]->is_used == 0)
			{
				philo->forks[is_right]->is_used = 1;
				success = 1;
			}
			pthread_mutex_unlock(&philo->forks[is_right]->lock);
		}
		if (success)
			return (0);
		usleep(100);
		curr_time = now(&philo->ate_time);
	}
	philo->is_died = 1;
	return (EXIT_FAILURE);
}

static int	philo_eat(struct s_philosopher *philo)
{
	int	curr_time;
	int	must_eat;

	if (philo->is_died)
		return (EXIT_FAILURE);
	must_eat = philo->common->number_of_times_each_philosopher_must_eat;
	if (get_fork(philo, 0) == 0)
	{
		philo_speak(philo, STATUS_FORK);
		if (get_fork(philo, 1) == 0)
		{
			philo->ate_count++;
			gettimeofday(&philo->ate_time, NULL);
			philo_speak(philo, STATUS_EAT);
			{
				curr_time = now(&philo->ate_time);
				while (curr_time < philo->common->time_to_die)
				{
					if (philo->common->done == 1)
						break ;
					if (curr_time >= philo->common->time_to_eat)
						break ;
					usleep(100);
					curr_time = now(&philo->ate_time);
				}
			}
			gettimeofday(&philo->ate_time, NULL);
			pthread_mutex_lock(&philo->forks[1]->lock);
			philo->forks[1]->is_used = 0;
			pthread_mutex_unlock(&philo->forks[1]->lock);
		}
		pthread_mutex_lock(&philo->forks[0]->lock);
		philo->forks[0]->is_used = 0;
		pthread_mutex_unlock(&philo->forks[0]->lock);
		if (must_eat && must_eat == philo->ate_count)
			return (EXIT_FAILURE);
		if (philo->is_died)
			return (EXIT_FAILURE);
		return (0);
	}
	return (EXIT_FAILURE);
}

void	*philo_do(void *param)
{
	struct s_philosopher *const	philo = param;
	struct s_common *const		common = philo->common;

	gettimeofday(&philo->ate_time, NULL);
	pthread_mutex_lock(&philo->common->lock);
	ft_memcpy(&philo->ate_time, &common->start_time, sizeof(struct timeval));
	pthread_mutex_unlock(&philo->common->lock);
	if (philo->thread_id % 2)
		usleep(100);
	while (philo->is_died == 0)
	{
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
		philo_speak(philo, STATUS_THINK);
	}
	if (philo->is_died == 0)
		return (NULL);
	pthread_mutex_lock(&philo->common->lock);
	philo->common->done = 1;
	pthread_mutex_unlock(&philo->common->lock);
	philo_speak(philo, STATUS_DIED);
	return (NULL);
}
