/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:33:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/11 18:46:21 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_speak(struct s_philosopher *philo, const char *status)
{
	struct s_common *const	common = philo->common;
	int						curr_time;

	if (philo->thread_stop)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&common->lock);
	{
		if (common->done >= common->number_of_philosophers)
			philo->thread_stop = 1;
		else
		{
			gettimeofday(&philo->log_time, NULL);
			curr_time = timediff(&common->start_time, &philo->log_time);
			if (timediff(&philo->ate_time, NULL) < common->time_to_die)
				printf("%d\t%d%s", curr_time, philo->thread_num, status);
			else
			{
				philo->thread_stop = 1;
				common->done = common->number_of_philosophers;
				printf("%d\t%d%s", curr_time, philo->thread_num, STATUS_DIED);
			}
		}
	}
	pthread_mutex_unlock(&common->lock);
	return (0);
}

static int	get_fork(struct s_philosopher *philo, int is_second)
{
	struct s_common *const	common = philo->common;
	struct s_fork *const	fork = philo->forks[is_second];
	int						success;

	success = 0;
	while (timediff(&philo->ate_time, NULL) < common->time_to_die)
	{
		if (philo->thread_stop)
			return (EXIT_FAILURE);
		if (is_second == 0 || philo->forks[0] != philo->forks[1])
		{
			pthread_mutex_lock(&fork->lock);
			if (fork->is_used == 0)
			{
				fork->is_used = 1;
				success = 1;
			}
			pthread_mutex_unlock(&fork->lock);
			if (success)
				return (0);
		}
		usleep(200);
	}
	_speak(philo, STATUS_DIED);
	return (EXIT_FAILURE);
}

static void	_eat(struct s_philosopher *philo)
{
	struct s_common *const	common = philo->common;

	if (get_fork(philo, 0))
		return ;
	_speak(philo, STATUS_FORK);
	if (get_fork(philo, 1) == 0)
	{
		_speak(philo, STATUS_EAT);
		philo->ate_count++;
		gettimeofday(&philo->ate_time, NULL);
		while (timediff(&philo->log_time, NULL) < common->time_to_eat)
			usleep(200);
		pthread_mutex_lock(&philo->forks[1]->lock);
		philo->forks[1]->is_used = 0;
		pthread_mutex_unlock(&philo->forks[1]->lock);
	}
	pthread_mutex_lock(&philo->forks[0]->lock);
	philo->forks[0]->is_used = 0;
	pthread_mutex_unlock(&philo->forks[0]->lock);
}

static int	_sleep_think(struct s_philosopher *philo)
{
	_speak(philo, STATUS_SLEEP);
	while (1)
	{
		if (philo->thread_stop)
			return (EXIT_FAILURE);
		if (timediff(&philo->ate_time, NULL) >= philo->common->time_to_die)
		{
			_speak(philo, STATUS_DIED);
			return (EXIT_FAILURE);
		}
		if (timediff(&philo->log_time, NULL) >= philo->common->time_to_sleep)
			break ;
	}
	usleep(200);
	_speak(philo, STATUS_THINK);
	return (0);
}

void	*philo_do(void *param)
{
	struct s_philosopher *const	philo = param;
	struct s_common *const		common = philo->common;
	int							must_eat;

	must_eat = common->number_of_times_each_philosopher_must_eat;
	pthread_mutex_lock(&common->lock);
	ft_memcpy(&philo->ate_time, &common->start_time, sizeof(struct timeval));
	ft_memcpy(&philo->log_time, &common->start_time, sizeof(struct timeval));
	pthread_mutex_unlock(&common->lock);
	if (philo->thread_num % 2)
		usleep(200);
	while (1)
	{
		_eat(philo);
		if (must_eat == 0 || (must_eat > 0 && must_eat == philo->ate_count))
		{
			pthread_mutex_lock(&common->lock);
			common->done++;
			pthread_mutex_unlock(&common->lock);
		}
		if (_sleep_think(philo))
			break ;
	}
	return (NULL);
}
