/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:48:10 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/24 03:12:26 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTIL_H
# define FT_UTIL_H
# include <stddef.h>
# include <errno.h>
# include <limits.h>

extern long	ft_atol(const char *str);
extern void	*ft_calloc(size_t count, size_t size);
#endif
