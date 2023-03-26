/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shared.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:23:08 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/27 05:47:55 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shared.h"

long	get_shared(struct s_shared *shared)
{
	long	val;

	pthread_mutex_lock(&shared->lock);
	val = shared->val;
	pthread_mutex_unlock(&shared->lock);
	return (val);
}

void	set_shared(struct s_shared *shared, long value)
{
	pthread_mutex_lock(&shared->lock);
	shared->val = value;
	pthread_mutex_unlock(&shared->lock);
}

void	adjust_shared(struct s_shared *shared, long delta)
{
	pthread_mutex_lock(&shared->lock);
	shared->val += delta;
	pthread_mutex_unlock(&shared->lock);
}
