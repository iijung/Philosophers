/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:20:29 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/07 16:20:56 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	while (s && s[len])
	{
		if (++len == SIZE_MAX)
		{
			write(fd, s, len);
			s += len;
			len = 0;
		}
	}
	write(fd, s, len);
}
