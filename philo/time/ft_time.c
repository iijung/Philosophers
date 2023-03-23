/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:01:33 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/23 15:18:29 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

struct timeval	add_timeval_ms(struct timeval base, int timestamp_in_ms)
{
	struct timeval	new_time;

	new_time = base;
	new_time.tv_sec += timestamp_in_ms / 1000;
	new_time.tv_usec += timestamp_in_ms % 1000 * 1000;
	return (new_time);
}

int	get_elapsed_ms(struct timeval base, struct timeval curr)
{
	int	elapsed_ms;

	elapsed_ms = (curr.tv_sec - base.tv_sec) * 1000;
	elapsed_ms += (curr.tv_usec - base.tv_usec) / 1000;
	return (elapsed_ms);
}

int	compare_timeval(struct timeval base, struct timeval curr)
{
	if (base.tv_sec < curr.tv_sec)
		return (TIME_REMAINING);
	if (base.tv_sec > curr.tv_sec)
		return (TIME_PASSED);
	if (base.tv_usec < curr.tv_usec)
		return (TIME_REMAINING);
	if (base.tv_usec > curr.tv_usec)
		return (TIME_PASSED);
	return (TIME_EQUAL);
}
