/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:34:24 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/30 04:35:23 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "share.h"

int	create_share(t_share *share)
{
	return (pthread_mutex_init(&share->lock, NULL));
}

void	destroy_share(t_share *share)
{
	pthread_mutex_destroy(&share->lock);
}

int	get_share(t_share *share)
{
	int	err;

	err = -1;
	pthread_mutex_lock(&share->lock);
	if (share->is_locked == UNLOCKED)
	{
		err = 0;
		share->is_locked = LOCKED;
	}
	pthread_mutex_unlock(&share->lock);
	return (err);
}

void	put_share(t_share *share)
{
	pthread_mutex_lock(&share->lock);
	share->is_locked = UNLOCKED;
	pthread_mutex_unlock(&share->lock);
}
