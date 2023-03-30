/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:34:24 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/29 18:30:32 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "share_bonus.h"

t_share	*create_share(const char *name, unsigned int num)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, num));
}

void	destroy_share(const char *name, t_share *share)
{
	sem_close(share);
	sem_unlink(name);
}

int	get_share(t_share *share)
{
	return (sem_wait(share));
}

void	put_share(t_share *share)
{
	sem_post(share);
}
