/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:33:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 21:51:33 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	_speak(struct s_philosopher *philo, const char *status)
{
	struct s_common *const	common = philo->common;
	int						ret;

	ret = EXIT_FAILURE;
	pthread_mutex_lock(&common->lock);
	{
		if (common->should_terminate == 0)
		{
			philo->log_time = get_elapsed_ms(common->start_time);
			if (philo->die_time <= philo->log_time)
			{
				status = STATUS_DIED;
				common->should_terminate = 1;
			}
			else
				ret = EXIT_SUCCESS;
			printf("%-20ld %20ld %s", philo->log_time, philo->num, status);
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
			return (EXIT_SUCCESS);
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
			return (EXIT_SUCCESS);
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
	ret = EXIT_FAILURE;
	if (!_speak(philo, STATUS_THINK) && !_fork(philo, philo->forks[0]))
	{
		if (philo->forks[0] == philo->forks[1])
			ret = _wait(philo, LONG_MAX);
		else if (!_speak(philo, STATUS_FORK) && !_fork(philo, philo->forks[1]))
		{
			if (!_speak(philo, STATUS_EAT))
			{
				philo->die_time = philo->log_time + common->time_to_die;
				ret = _wait(philo, common->time_to_eat);
				philo->ate_count++;
				if (must_eat != -1 && philo->ate_count >= must_eat)
					ret = EXIT_FAILURE;
			}
			put_fork(philo->forks[1]);
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
		usleep(500);
	}
	return (NULL);
}
