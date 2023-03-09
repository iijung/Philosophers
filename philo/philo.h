/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:44:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/10 05:49:02 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include "util.h"

# define STATUS_FORK	" has taken a fork\n"
# define STATUS_EAT		" is eating\n"
# define STATUS_SLEEP	" is sleeping\n"
# define STATUS_THINK	" is thinking\n"
# define STATUS_DIED	" died\n"

struct s_common
{
	int						number_of_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_times_each_philosopher_must_eat;
	struct timeval			start_time;
	pthread_mutex_t			lock;
	struct
	{
		int					done;
		int					exit_status;
	};
};

struct s_fork
{
	pthread_mutex_t			lock;
	int						is_used;
};

struct s_philosopher
{
	pthread_t				thread_id;
	int						thread_num;
	int						thread_stop;
	int						ate_count;
	struct timeval			ate_time;
	struct timeval			log_time;
	struct
	{
		struct s_common			*common;
		struct s_fork			*forks[2];
	};
};

struct s_simulator
{
	struct s_common			common;
	struct s_fork			*forks;
	struct s_philosopher	*philos;
};

extern int	initial(struct s_simulator *simulator, int argc, char *argv[]);
extern void	finally(struct s_simulator *simulator);
#endif
