/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shared.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:08:42 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/27 03:12:29 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHARED_H
# define  FT_SHARED_H
# include <pthread.h>

struct s_shared_lock
{
	pthread_mutex_t	lock;
	int				val;
};

void	set_shared(struct s_shared *shared, int value);
int		get_shared(struct s_shared *shared);

#endif
