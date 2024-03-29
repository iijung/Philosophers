/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:33:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/30 13:51:54 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"
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
		{
			printf("%-20ld %20ld %s", philo->log_time, philo->num, STATUS_DIED);
			kill(0, SIGINT);
		}
		else
			ret = PHILO_INPROGRESS;
		printf("%-20ld %20ld %s", philo->log_time, philo->num, status);
	}
	sem_post(common->lock);
	if (common->number_of_times_each_philosopher_must_eat == philo->ate_count
		&& common->number_of_times_each_philosopher_must_eat != -1)
		put_share(common->counter);
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
	int							ret;

	ret = PHILO_ERROR;
	if (!_speak(philo, STATUS_THINK) && !get_share(philo->forks))
	{
		if (!_speak(philo, STATUS_FORK))
		{
			if (common->number_of_philosophers == 1)
				ret = _wait(philo, LONG_MAX);
			else if (!get_share(philo->forks))
			{
				if (!_speak(philo, STATUS_FORK) && !_speak(philo, STATUS_EAT))
				{
					philo->die_time = philo->log_time + common->time_to_die;
					ret = _wait(philo, common->time_to_eat);
					philo->ate_count++;
				}
				put_share(philo->forks);
			}
		}
		put_share(philo->forks);
	}
	return (ret);
}

int	philo_do(void *param)
{
	struct s_philosopher *const	philo = param;
	struct s_common *const		common = philo->common;

	get_share(common->counter);
	philo->die_time = common->time_to_die;
	while (1)
	{
		if (_eat(philo))
			break ;
		if (_speak(philo, STATUS_SLEEP) || _wait(philo, common->time_to_sleep))
			break ;
	}
	return (PHILO_ERROR);
}
