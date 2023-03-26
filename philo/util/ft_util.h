/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:48:10 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/26 23:18:22 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTIL_H
# define FT_UTIL_H
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

extern long	ft_atol(const char *str);
extern void	ft_putstr_fd(char *s, int fd);
extern void	*ft_calloc(size_t count, size_t size);
#endif
