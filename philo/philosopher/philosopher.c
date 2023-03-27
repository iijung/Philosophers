/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:33:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/27 23:56:45 by minjungk         ###   ########.fr       */
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
		printf("%-20ld %20ld %s",
			get_elapsed_ms(common->start_time, philo->log_time),
			philo->num, status);
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

static int	_fork(struct s_philosopher *philo, int is_second)
{
	struct s_shared	*const	fork = philo->forks[is_second];
	const int				same_fork = philo->forks[0] == philo->forks[1];
	int						success;

	success = 0;
	while (compare_timenow(philo->die_time) != TIME_PASSED)
	{
		if (same_fork == 0)
		{
			pthread_mutex_lock(&fork->lock);
			if (fork->val == 0)
			{
				fork->val = 1;
				success = 1;
			}
			pthread_mutex_unlock(&fork->lock);
			if (success)
				return (EXIT_SUCCESS);
		}
		usleep(200);
	}
	return (_speak(philo, STATUS_DIED));
}

static int	_eat(struct s_philosopher *philo)
{
	struct s_common *const		common = philo->common;
	long						must_eat;

	if (_speak(philo, STATUS_EAT))
		return (EXIT_FAILURE);
	must_eat = common->number_of_times_each_philosopher_must_eat;
	philo->ate_count++;
	philo->die_time = add_timeval_ms(philo->log_time, common->time_to_die);
	if (_wait(philo, common->time_to_eat))
		return (EXIT_FAILURE);
	if (philo->ate_count == must_eat)
		adjust_shared(&common->completed, 1);
	set_shared(philo->forks[1], 0);
	set_shared(philo->forks[0], 0);
	return (EXIT_SUCCESS);
}

void	*philo_do(void *param)
{
	struct s_philosopher *const	philo = param;
	struct s_common *const		common = philo->common;

	philo->die_time = add_timeval_ms(common->start_time, common->time_to_die);
	while (_speak(philo, STATUS_THINK) == EXIT_SUCCESS)
	{
		if (_fork(philo, 0) || _speak(philo, STATUS_FORK))
			break ;
		if (_fork(philo, 1) || _eat(philo))
			break ;
		if (_speak(philo, STATUS_SLEEP) || _wait(philo, common->time_to_sleep))
			break ;
		usleep(500);
	}
	set_shared(&common->completed, common->number_of_philosophers);
	return (NULL);
}
