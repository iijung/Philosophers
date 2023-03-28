/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:39:46 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 23:59:15 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H
# include <fcntl.h>
# include <semaphore.h>

typedef sem_t	t_fork;

t_fork		*create_fork(long num_of_fork);
extern void	destroy_fork(t_fork *fork);
extern int	get_fork(t_fork *fork);
extern void	put_fork(t_fork *fork);

#endif
