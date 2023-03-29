/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:31:20 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/29 18:31:21 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATE_BONUS_H
# define SIMULATE_BONUS_H
# include "philosopher_bonus.h"

struct s_simulator
{
	struct s_common			*common;
	struct s_philosopher	*philos;
	t_share					*forks;
};

extern int	simulate(struct s_common *common);
#endif
