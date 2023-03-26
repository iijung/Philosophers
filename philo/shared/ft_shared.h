/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shared.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:08:42 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/27 05:47:46 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHARED_H
# define  FT_SHARED_H
# include <pthread.h>

struct s_shared
{
	pthread_mutex_t	lock;
	long			val;
};

long	get_shared(struct s_shared *shared);
void	set_shared(struct s_shared *shared, long value);
void	adjust_shared(struct s_shared *shared, long delta);

#endif
