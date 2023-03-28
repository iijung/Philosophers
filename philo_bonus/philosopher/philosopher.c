/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:33:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/29 00:11:22 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <limits.h>

static int	_speak(struct s_philosopher *philo, const char *status)
{
	struct s_common *const	common = philo->common;
	int						ret;

	ret = PHILO_ERROR;
	sem_wait(common->lock);
	{
		philo->log_time = get_elapsed_ms(common->start_time);
		if (philo->die_time <= philo->log_time)
			status = STATUS_DIED;
		else
			ret = PHILO_INPROGRESS;
		printf("%-20ld %20ld %s", philo->log_time, philo->num, status);
	}
	sem_post(common->lock);
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

static int	_eat(struct s_philosopher *philo)
{
	struct s_common *const		common = philo->common;
	long						must_eat;
	int							ret;

	must_eat = common->number_of_times_each_philosopher_must_eat;
	ret = PHILO_ERROR;
	if (!_speak(philo, STATUS_THINK) && !get_fork(philo->forks))
	{
		if (!_speak(philo, STATUS_FORK) && !get_fork(philo->forks))
		{
			if (!_speak(philo, STATUS_EAT))
			{
				philo->die_time = philo->log_time + common->time_to_die;
				ret = _wait(philo, common->time_to_eat);
				philo->ate_count++;
				if (must_eat != -1 && philo->ate_count >= must_eat)
					ret = PHILO_COMPLETED;
			}
			put_fork(philo->forks);
		}
		put_fork(philo->forks);
	}
	return (ret);
}

int	philo_do(void *param)
{
	struct s_philosopher *const	philo = param;
	struct s_common *const		common = philo->common;
	long						must_eat;

	must_eat = common->number_of_times_each_philosopher_must_eat;
	philo->die_time = common->time_to_die;
	while (1)
	{
		if (_eat(philo))
			break ;
		if (_speak(philo, STATUS_SLEEP) || _wait(philo, common->time_to_sleep))
			break ;
		usleep(500);
	}
	if (must_eat != -1 && philo->ate_count >= must_eat)
		return (PHILO_COMPLETED);
	return (PHILO_ERROR);
}
