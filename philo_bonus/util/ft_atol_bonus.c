/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:23:23 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 23:12:24 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <errno.h>
#include <limits.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

long	ft_atol(const char *str)
{
	long	num;
	int		is_negative;

	num = 0;
	while (ft_isspace(*str))
		++str;
	is_negative = 0;
	if (*str == '+' || *str == '-')
		is_negative = (*str++ == '-');
	while (ft_isdigit(*str))
	{
		if (num > (LONG_MAX - (*str - '0')) / 10)
		{
			errno = ERANGE;
			if (is_negative)
				return (LONG_MIN);
			else
				return (LONG_MAX);
		}
		num = (num * 10) + (*str - '0');
		++str;
	}
	if (is_negative)
		return (-num);
	return (num);
}
