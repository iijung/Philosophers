/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:31:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/30 15:06:56 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATE_BONUS_H
# define SIMULATE_BONUS_H
# include "philosopher_bonus.h"
# include <stdlib.h>		// malloc, free
# include <string.h>		// memset
# include <sys/wait.h>		// usleep

struct s_simulator
{
	struct s_common			*common;
	struct s_philosopher	*philos;
	t_share					*forks;
};

extern void	*ft_calloc(size_t count, size_t size);
extern int	simulate(struct s_common *common);
#endif
