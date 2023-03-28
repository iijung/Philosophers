/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:34:24 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 23:59:46 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

t_fork	*create_fork(long num_of_fork)
{
	sem_unlink("fork");
	return (sem_open("fork", O_CREAT | O_EXCL, 0644, num_of_fork));
}

void	destroy_fork(t_fork *fork)
{
	sem_close(fork);
	sem_unlink("fork");
}

int	get_fork(t_fork *fork)
{
	return (sem_wait(fork));
}

void	put_fork(t_fork *fork)
{
	sem_post(fork);
}
