/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:34:24 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 21:07:03 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

int	create_fork(t_fork *fork)
{
	return (pthread_mutex_init(&fork->lock, NULL));
}

void	destroy_fork(t_fork *fork)
{
	pthread_mutex_destroy(&fork->lock);
}

int	get_fork(t_fork *fork)
{
	int	err;

	err = -1;
	pthread_mutex_lock(&fork->lock);
	if (fork->is_used == USE_NO)
	{
		err = 0;
		fork->is_used = USE_YES;
	}
	pthread_mutex_unlock(&fork->lock);
	return (err);
}

void	put_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->lock);
	fork->is_used = USE_NO;
	pthread_mutex_unlock(&fork->lock);
}
