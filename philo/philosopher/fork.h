/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:39:46 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 20:43:56 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H
# include <pthread.h>

typedef struct s_fork	t_fork;

enum e_use
{
	USE_NO = 0,
	USE_YES = 1
};

struct s_fork
{
	pthread_mutex_t	lock;
	enum e_use		is_used;
};

extern int	create_fork(t_fork *fork);
extern void	destroy_fork(t_fork *fork);
extern int	get_fork(t_fork *fork);
extern void	put_fork(t_fork *fork);

#endif
