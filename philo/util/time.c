/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:01:33 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/08 01:25:58 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>

extern int	now(struct timeval *start_time)
{
	struct timeval	curr_time;
	int				timestamp_in_ms;

	if (start_time == NULL)
		return (0);
	gettimeofday(&curr_time, NULL);
	timestamp_in_ms = (curr_time.tv_sec - start_time->tv_sec) * 1000;
	timestamp_in_ms += (curr_time.tv_usec - start_time->tv_usec) / 1000;
	return (timestamp_in_ms);
}
