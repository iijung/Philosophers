/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:56:47 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/10 23:05:15 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*ft_sem_open(const char *prefix, int id)
{
	char	name[30];
	int		i;
	int		prefix_len;

	prefix_len = 0;
	while (prefix && prefix[prefix_len] && prefix_len < 10)
		++prefix_len;
	ft_memset(name, 0, sizeof(name));
	ft_memcpy(name, prefix, prefix_len);
	i = prefix_len;
	while (id > 0)
	{
		name[i++] = "0123456789"[id % 10];
		id /= 10;
	}
	return (sem_open(name, O_CREAT | O_EXCL, 0644, 1));
}
