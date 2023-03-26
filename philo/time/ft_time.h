/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:09:39 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/27 05:56:22 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H
# include <stddef.h>
# include <sys/time.h>

enum e_time
{
	TIME_REMAINING = 1,
	TIME_EQUAL = 0,
	TIME_PASSED = -1
};

struct timeval	add_timeval_ms(struct timeval base, long timestamp_in_ms);
long			get_elapsed_ms(struct timeval base, struct timeval curr);
int				compare_timeval(struct timeval base, struct timeval curr);
int				compare_timenow(struct timeval base);
#endif
