/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:27:14 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/30 15:04:42 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*rtn;

	rtn = malloc(count * size);
	if (rtn)
		memset(rtn, 0, count * size);
	return (rtn);
}
