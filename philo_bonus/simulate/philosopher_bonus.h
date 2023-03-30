/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:17:48 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/29 18:58:10 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H
# include <stdio.h>			// printf
# include <unistd.h>		// usleep
# include <signal.h>		// kill
# include <sys/time.h>		// gettimeofday
# include "share_bonus.h"

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
		t_share			*lock;
		t_share			*counter;
	};
};

struct s_philosopher
{
	pid_t				pid;
	long				num;
	long				ate_count;
	long				die_time;
	long				log_time;
	struct
	{
		struct s_common	*common;
		t_share			*forks;
	};
};

long	get_elapsed_ms(struct timeval base);
int		philo_do(void *param);
#endif
