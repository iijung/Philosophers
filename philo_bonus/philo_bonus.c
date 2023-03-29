/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:01:16 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/30 06:16:18 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulate_bonus.h"
#include <errno.h>
#include <limits.h>

extern void	ft_putstr_fd(char *s, int fd);
extern long	ft_atol(const char *str);

int	main(int argc, char *argv[])
{
	static struct s_common	common;

	if (argv && (argc == 5 || argc == 6))
	{
		common.number_of_philosophers = ft_atol(argv[1]);
		common.time_to_die = ft_atol(argv[2]);
		common.time_to_eat = ft_atol(argv[3]);
		common.time_to_sleep = ft_atol(argv[4]);
		common.number_of_times_each_philosopher_must_eat = -1;
		if (argc == 6)
			common.number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
		if (errno == 0
			&& common.time_to_die >= 0
			&& common.time_to_eat >= 0
			&& common.time_to_sleep >= 0
			&& common.number_of_philosophers <= UINT_MAX)
			return (simulate(&common));
	}
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd(
		" number_of_philosophers"
		" time_to_die time_to_eat time_to_sleep"
		" [number_of_times_each_philosophers_must_eat]\n", STDERR_FILENO);
	return (-1);
}
