/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:48:10 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/08 01:19:32 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

extern int	now(struct timeval *start_time);
extern void	*ft_calloc(size_t count, size_t size);
extern void	*ft_memcpy(void *dst, const void *src, size_t n);
#endif
