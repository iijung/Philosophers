/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:33:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/11 18:24:03 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_speak(struct s_philosopher *philo, const char *status)
{
	struct s_common *const	common = philo->common;
	int						curr_time;

	if (philo->process_stop)
		return (EXIT_FAILURE);
	sem_wait(common->lock);
	{
		gettimeofday(&philo->log_time, NULL);
		curr_time = timediff(&common->start_time, &philo->log_time);
		if (timediff(&philo->ate_time, NULL) < common->time_to_die)
			printf("%d\t%d%s", curr_time, philo->process_num, status);
		else
		{
			philo->process_stop = 1;
			printf("%d\t%d%s", curr_time, philo->process_num, STATUS_DIED);
		}
	}
	sem_post(common->lock);
	return (0);
}

static void	_eat(struct s_philosopher *philo)
{
	struct s_common *const	common = philo->common;

	sem_wait(philo->forks[0]->lock);
	{
		_speak(philo, STATUS_FORK);
		if (philo->forks[0] == philo->forks[1])
		{
			while (timediff(&philo->ate_time, NULL) < common->time_to_die)
				usleep(200);
			_speak(philo, STATUS_DIED);
			exit(EXIT_FAILURE);
		}
		sem_wait(philo->forks[1]->lock);
		{
			_speak(philo, STATUS_EAT);
			philo->ate_count++;
			while (timediff(&philo->log_time, NULL) < common->time_to_eat)
				usleep(200);
			gettimeofday(&philo->ate_time, NULL);
		}
		sem_post(philo->forks[1]->lock);
	}
	sem_post(philo->forks[0]->lock);
}

static int	_sleep_think(struct s_philosopher *philo)
{
	_speak(philo, STATUS_SLEEP);
	while (1)
	{
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

extern int	philo_do(void *param)
{
	struct s_philosopher *const	philo = param;
	struct s_common *const		common = philo->common;
	int							must_eat;

	must_eat = common->number_of_times_each_philosopher_must_eat;
	sem_wait(common->lock);
	gettimeofday(&common->start_time, NULL);
	ft_memcpy(&philo->ate_time, &common->start_time, sizeof(struct timeval));
	ft_memcpy(&philo->log_time, &common->start_time, sizeof(struct timeval));
	sem_post(common->lock);
	if (philo->process_num % 2)
		usleep(200);
	while (1)
	{
		_eat(philo);
		if (must_eat == 0 || (must_eat > 0 && must_eat == philo->ate_count))
			break ;
		if (_sleep_think(philo))
			break ;
	}
	if (philo->process_stop)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
