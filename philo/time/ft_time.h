/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:09:39 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/23 15:39:29 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H
# include <sys/time.h>

enum e_time
{
	TIME_REMAINING,
	TIME_EQUAL,
	TIME_PASSED
};

struct timeval	add_timeval_ms(struct timeval base, int timestamp_in_ms);
int				get_elapsed_ms(struct timeval base, struct timeval curr);
int				compare_timeval(struct timeval base, struct timeval curr);
#endif
