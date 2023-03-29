/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:23:23 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/30 03:23:06 by minjungk         ###   ########.fr       */
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

static long	_overflow(long num, char digit, int is_negative)
{
	if (num > (LONG_MAX - (digit - '0')) / 10)
	{
		errno = ERANGE;
		if (is_negative)
			return (LONG_MIN);
		else
			return (LONG_MAX);
	}
	return (0);
}

long	ft_atol(const char *str)
{
	long	num;
	long	overflow;
	int		is_negative;

	num = 0;
	while (ft_isspace(*str))
		++str;
	is_negative = 0;
	if (*str == '+' || *str == '-')
		is_negative = (*str++ == '-');
	if (ft_isdigit(*str))
		errno = EINVAL;
	while (ft_isdigit(*str))
	{
		overflow = _overflow(num, *str, is_negative);
		if (overflow)
			return (overflow);
		num = (num * 10) + (*str++ - '0');
	}
	if (is_negative)
		return (-num);
	return (num);
}
