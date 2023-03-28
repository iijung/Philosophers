/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:01:16 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/28 15:32:27 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulate.h"

int	main(int argc, char *argv[])
{
	struct s_common	common;

	memset(&common, 0, sizeof(struct s_common));
	if (argv && (argc == 5 || argc == 6))
	{
		common.number_of_philosophers = ft_atol(argv[1]);
		common.time_to_die = ft_atol(argv[2]);
		common.time_to_eat = ft_atol(argv[3]);
		common.time_to_sleep = ft_atol(argv[4]);
		common.number_of_times_each_philosopher_must_eat = -1;
		if (argc == 6)
			common.number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
		if (errno == 0)
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
