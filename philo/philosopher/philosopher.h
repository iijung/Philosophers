/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:17:48 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/27 04:02:19 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include "ft_util.h"
# include "ft_time.h"
# include "ft_shared.h"

# define STATUS_FORK	" has taken a fork\n"
# define STATUS_EAT		" is eating\n"
# define STATUS_SLEEP	" is sleeping\n"
# define STATUS_THINK	" is thinking\n"
# define STATUS_DIED	" died\n"

struct s_common
{
	long				number_of_philosophers;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_times_each_philosopher_must_eat;
	struct timeval		start_time;
	pthread_mutex_t		lock;
	struct s_shared		completed;
};

struct s_philosopher
{
	pthread_t			thread_id;
	long				thread_num;
	long				ate_count;
	struct timeval		die_time;
	struct timeval		log_time;
	struct
	{
		struct s_common	*common;
		struct s_shared	*forks[2];
	};
};

void	*philo_do(void *param);
#endif
