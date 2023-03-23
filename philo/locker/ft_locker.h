/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_locker.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:08:42 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/23 18:02:21 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LOCKER_H
# define  FT_LOCKER_H

enum e_locker_action
{
	UNLOCKED = 0,
	LOCKED = 1
};

struct s_locker
{
	pthread_mutex_t	key;
	int				is_locked;
};

int	ft_lock_unlock(struct s_locker *locker, enum e_lock action);

#endif
