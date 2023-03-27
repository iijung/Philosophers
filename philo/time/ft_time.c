/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:01:33 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 00:50:39 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"

struct timeval	add_timeval_ms(struct timeval base, long timestamp_in_ms)
{
	base.tv_sec += timestamp_in_ms / 1000;
	base.tv_usec += timestamp_in_ms % 1000 * 1000;
	if (base.tv_usec >= 1000000)
	{
		base.tv_sec += 1;
		base.tv_usec -= 1000000;
	}
	return (base);
}

long	get_elapsed_ms(struct timeval base, struct timeval curr)
{
	long	elapsed_ms;

	elapsed_ms = (curr.tv_sec - base.tv_sec) * 1000;
	elapsed_ms += (curr.tv_usec - base.tv_usec) / 1000;
	return (elapsed_ms);
}

int	compare_timeval(struct timeval base, struct timeval curr)
{
	if (base.tv_sec > curr.tv_sec)
		return (TIME_REMAINING);
	if (base.tv_sec < curr.tv_sec)
		return (TIME_PASSED);
	if (base.tv_usec > curr.tv_usec)
		return (TIME_REMAINING);
	if (base.tv_usec < curr.tv_usec)
		return (TIME_PASSED);
	return (TIME_EQUAL);
}

int	compare_timenow(struct timeval base)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	if (base.tv_sec > curr.tv_sec)
		return (TIME_REMAINING);
	if (base.tv_sec < curr.tv_sec)
		return (TIME_PASSED);
	if (base.tv_usec > curr.tv_usec)
		return (TIME_REMAINING);
	if (base.tv_usec < curr.tv_usec)
		return (TIME_PASSED);
	return (TIME_EQUAL);
}
