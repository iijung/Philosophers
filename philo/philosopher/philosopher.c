/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:33:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/29 17:22:44 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <limits.h>

static int	_speak(struct s_philosopher *philo, const char *status)
{
	struct s_common *const	common = philo->common;
	int						ret;
	long					must_eat;

	ret = PHILO_ERROR;
	must_eat = common->number_of_times_each_philosopher_must_eat;
	pthread_mutex_lock(&common->lock);
	{
		if (common->end_counter < common->number_of_philosophers)
		{
			philo->log_time = get_elapsed_ms(common->start_time);
			if (philo->die_time <= philo->log_time)
			{
				status = STATUS_DIED;
				common->end_counter = common->number_of_philosophers;
			}
			else
				ret = PHILO_INPROGRESS;
			printf("%-20ld %20ld %s", philo->log_time, philo->num, status);
			if (must_eat != -1 && philo->ate_count == must_eat)
				common->end_counter++;
		}
	}
	pthread_mutex_unlock(&common->lock);
	return (ret);
}

static int	_wait(struct s_philosopher *philo, long timestamp_in_ms)
{
	struct s_common *const	common = philo->common;
	const long				end_time = philo->log_time + timestamp_in_ms;
	long					curr_time;

	curr_time = get_elapsed_ms(common->start_time);
	while (curr_time < philo->die_time)
	{
		if (end_time <= curr_time)
			return (PHILO_INPROGRESS);
		usleep(500);
		curr_time = get_elapsed_ms(common->start_time);
	}
	return (_speak(philo, STATUS_DIED));
}

static int	_fork(struct s_philosopher *philo, t_fork *fork)
{
	struct s_common *const	common = philo->common;
	long					curr_time;

	curr_time = get_elapsed_ms(common->start_time);
	while (curr_time < philo->die_time)
	{
		if (get_fork(fork) == 0)
			return (PHILO_INPROGRESS);
		usleep(500);
		curr_time = get_elapsed_ms(common->start_time);
	}
	return (_speak(philo, STATUS_DIED));
}

static int	_eat(struct s_philosopher *philo)
{
	struct s_common *const		common = philo->common;
	int							ret;

	ret = PHILO_ERROR;
	if (!_speak(philo, STATUS_THINK) && !_fork(philo, philo->forks[0]))
	{
		if (!_speak(philo, STATUS_FORK))
		{
			if (common->number_of_philosophers == 1)
				ret = _wait(philo, LONG_MAX);
			else if (!_fork(philo, philo->forks[1]))
			{
				if (!_speak(philo, STATUS_EAT))
				{
					philo->die_time = philo->log_time + common->time_to_die;
					ret = _wait(philo, common->time_to_eat);
					philo->ate_count++;
				}
				put_fork(philo->forks[1]);
			}
		}
		put_fork(philo->forks[0]);
	}
	return (ret);
}

void	*philo_do(void *param)
{
	struct s_philosopher *const	philo = param;
	struct s_common *const		common = philo->common;

	philo->die_time = common->time_to_die;
	while (1)
	{
		if (_eat(philo))
			break ;
		if (_speak(philo, STATUS_SLEEP) || _wait(philo, common->time_to_sleep))
			break ;
	}
	return (NULL);
}
