/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:39:46 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/29 18:33:35 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARE_BONUS_H
# define SHARE_BONUS_H
# include <fcntl.h>
# include <semaphore.h>

# define SHARE_COMMON	"common"
# define SHARE_COUNTER	"counter"
# define SHARE_FORK		"fork"

typedef sem_t	t_share;

t_share		*create_share(const char *name, unsigned int num);
extern void	destroy_share(const char *name, t_share *share);
extern int	get_share(t_share *share);
extern void	put_share(t_share *share);

#endif
