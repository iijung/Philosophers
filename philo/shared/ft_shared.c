/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shared.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:23:08 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/27 03:21:20 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shared.h"

void	set_shared(struct s_shared_lock *shared, int value)
{
	pthread_mutex_lock(&shared->lock);
	shared->val = value;
	pthread_mutex_unlock(&shared->lock);
}

void	add_shared(struct s_shared_lock *shared)
{
	pthread_mutex_lock(&shared->lock);
	shared->val++;
	pthread_mutex_unlock(&shared->lock);
}

void	sub_shared(struct s_shared_lock *shared)
{
	pthread_mutex_lock(&shared->lock);
	shared->val--;
	pthread_mutex_unlock(&shared->lock);
}

int		get_shared(struct s_shared_lock *shared)
{
	int	val;

	pthread_mutex_lock(&shared->lock);
	val = shared->val;
	pthread_mutex_unlock(&shared->lock);
	return (val);
}
