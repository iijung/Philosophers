/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:01:33 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 20:15:52 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>

long	get_elapsed_ms(struct timeval base)
{
	struct timeval	curr;
	long			elapsed_ms;

	gettimeofday(&curr, NULL);
	elapsed_ms = (curr.tv_sec - base.tv_sec) * 1000;
	elapsed_ms += (curr.tv_usec - base.tv_usec) / 1000;
	return (elapsed_ms);
}
