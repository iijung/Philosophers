/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:33:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/27 07:44:38 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	_speak(struct s_philosopher *philo, const char *status)
{
	struct s_common *const	common = philo->common;
	int						ret;

	if (get_shared(&common->completed) >= common->number_of_philosophers)
		return (EXIT_FAILURE);
	ret = EXIT_SUCCESS;
	pthread_mutex_lock(&common->lock);
	{
		gettimeofday(&philo->log_time, NULL);
		if (compare_timeval(philo->die_time, philo->log_time) == TIME_PASSED)
		{
			ret = EXIT_FAILURE;
			status = STATUS_DIED;
			set_shared(&common->completed, common->number_of_philosophers);
		}
		printf("%ld\t%ld%s",
			get_elapsed_ms(common->start_time, philo->log_time),
			philo->thread_num, status);
	}
	pthread_mutex_unlock(&common->lock);
	return (ret);
}

static int	_wait(struct s_philosopher *philo, long timestamp_in_ms)
{
	struct timeval	end_time;

	end_time = add_timeval_ms(philo->log_time, timestamp_in_ms);
	while (compare_timenow(philo->die_time) != TIME_PASSED)
	{
		if (compare_timenow(end_time) == TIME_PASSED)
			return (EXIT_SUCCESS);
		usleep(200);
	}
	return (_speak(philo, STATUS_DIED));
}

static int	_eat(struct s_philosopher *philo)
{
	int						ret;
	struct s_common *const	common = philo->common;

	if (_speak(philo, STATUS_FORK) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo->forks[0] == philo->forks[1] && _wait(philo, LONG_MAX))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&philo->forks[1]->lock);
	if (_speak(philo, STATUS_EAT))
	{
		pthread_mutex_unlock(&philo->forks[1]->lock);
		return (EXIT_FAILURE);
	}
	philo->ate_count++;
	philo->die_time = add_timeval_ms(philo->log_time, common->time_to_die);
	if (_wait(philo, common->time_to_eat))
		ret = EXIT_FAILURE;
	if (philo->ate_count == common->number_of_times_each_philosopher_must_eat
		&& common->number_of_times_each_philosopher_must_eat != -1)
		adjust_shared(&common->completed, 1);
	pthread_mutex_unlock(&philo->forks[1]->lock);
	return (EXIT_SUCCESS);
}

void	*philo_do(void *param)
{
	struct s_philosopher *const	philo = param;
	struct s_common *const		common = philo->common;
	int							ret;

	pthread_mutex_lock(&common->lock);
	pthread_mutex_unlock(&common->lock);
	philo->die_time = add_timeval_ms(common->start_time, common->time_to_die);
	if (philo->thread_num % 2)
		usleep(200);
	while (1)
	{
		if (_speak(philo, STATUS_THINK))
			break ;
		pthread_mutex_lock(&philo->forks[0]->lock);
		ret = _eat(philo);
		pthread_mutex_unlock(&philo->forks[0]->lock);
		if (ret == EXIT_FAILURE)
			break ;
		if (_speak(philo, STATUS_SLEEP) || _wait(philo, common->time_to_sleep))
			break ;
	}
	set_shared(&common->completed, common->number_of_philosophers);
	return (NULL);
}
