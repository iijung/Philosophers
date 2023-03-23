/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_locker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:23:08 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/23 18:02:21 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_locker.h"

int	ft_lock_unlock(struct s_locker *locker, enum e_lock action)
{
	int	err;

	err = -1;
	if (locker == NULL)
		return (err);
	if (pthread_mutex_lock(&locker->key) == 0)
	{
		if (locker->is_locked == UNLOCKED)
		{
			locker->is_locked = action;
			err = 0;
		}
		pthread_mutex_unlock(&locker->key);
	}
	return (err);
}
