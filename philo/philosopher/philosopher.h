/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:17:48 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/24 03:20:47 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define STATUS_FORK	" has taken a fork\n"
# define STATUS_EAT		" is eating\n"
# define STATUS_SLEEP	" is sleeping\n"
# define STATUS_THINK	" is thinking\n"
# define STATUS_DIED	" died\n"

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

#endif
