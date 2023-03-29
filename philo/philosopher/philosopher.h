/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:17:48 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/30 04:35:01 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>			// printf
# include <unistd.h>		// usleep
# include <sys/time.h>		// gettimeofday
# include "share.h"

# define STATUS_FORK	"has taken a fork\n"
# define STATUS_EAT		"is eating\n"
# define STATUS_SLEEP	"is sleeping\n"
# define STATUS_THINK	"is thinking\n"
# define STATUS_DIED	"died\n"

enum e_status
{
	PHILO_INPROGRESS,
	PHILO_ERROR,
	PHILO_COMPLETED
};

struct s_common
{
	long				number_of_philosophers;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_times_each_philosopher_must_eat;
	struct timeval		start_time;
	struct
	{
		pthread_mutex_t	lock;
		long			end_counter;
	};
};

struct s_philosopher
{
	pthread_t			tid;
	long				num;
	long				ate_count;
	long				die_time;
	long				log_time;
	struct
	{
		struct s_common	*common;
		t_share			*forks[2];
	};
};

long	get_elapsed_ms(struct timeval base);
void	*philo_do(void *param);
#endif
