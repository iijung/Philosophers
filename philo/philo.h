/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:44:36 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/24 05:42:55 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <pthread.h>
# include <unistd.h>
# include "util/ft_util.h"
# include "time/ft_time.h"

struct s_common
{
	long					number_of_philosophers;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					number_of_times_each_philosopher_must_eat;
	struct timeval			start_time;
	struct s_locker			lock;
};

#endif
