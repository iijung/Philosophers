/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:31:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/30 04:39:59 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATE_H
# define SIMULATE_H
# include "philosopher.h"
# include <stdlib.h>		// malloc, free
# include <string.h>		// memset

struct s_simulator
{
	struct s_common			*common;
	struct s_philosopher	*philos;
	t_share					*forks;
};

extern void	*ft_calloc(size_t count, size_t size);
extern int	simulate(struct s_common *common);
#endif
