/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:31:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/29 00:02:31 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATE_H
# define SIMULATE_H
# include "philosopher.h"
# include <signal.h>

struct s_simulator
{
	struct s_common			*common;
	struct s_philosopher	*philos;
	t_fork					*forks;
};

extern int	simulate(struct s_common *common);
#endif
