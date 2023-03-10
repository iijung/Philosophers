/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:48:10 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/10 23:05:17 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

extern int	timediff(struct timeval *base, struct timeval *curr);
extern void	*ft_calloc(size_t count, size_t size);
extern void	*ft_memcpy(void *dst, const void *src, size_t n);
#endif
