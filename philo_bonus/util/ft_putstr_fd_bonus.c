/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:29:45 by minjungk          #+#    #+#             */
/*   Updated: 2024/08/09 23:17:47 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	ssize_t	len;

	len = 0;
	while (s && s[len])
	{
		if (++len < 1024)
			continue ;
		if (len != write(fd, s, len))
			return ;
		s += len;
		len = 0;
	}
	if (len != write(fd, s, len))
		return ;
}
