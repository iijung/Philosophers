/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:39:46 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/30 04:34:41 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARE_H
# define SHARE_H
# include <pthread.h>

typedef struct s_share	t_share;

enum e_lock
{
	UNLOCKED = 0,
	LOCKED = 1
};

struct s_share
{
	pthread_mutex_t	lock;
	enum e_lock		is_locked;
};

extern int		create_share(t_share *share);
extern void		destroy_share(t_share *share);
extern int		get_share(t_share *share);
extern void		put_share(t_share *share);

#endif
