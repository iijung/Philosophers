/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:01:33 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/10 03:29:21 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>

extern int	timediff(struct timeval *base, struct timeval *curr)
{
	struct timeval	now;
	int				timestamp_in_ms;

	if (base == NULL)
		return (0);
	gettimeofday(&now, NULL);
	if (curr == NULL)
		curr = &now;
	timestamp_in_ms = curr->tv_sec * 1000 - base->tv_sec * 1000;
	timestamp_in_ms += curr->tv_usec / 1000 - base->tv_usec / 1000;
	return (timestamp_in_ms);
}
