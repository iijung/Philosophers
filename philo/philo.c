/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:01:16 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/10 05:43:07 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

extern void	*philo_do(void *param);

static void	simulate(struct s_simulator *simulator)
{
	int						i;
	struct s_philosopher	*philo;

	pthread_mutex_lock(&simulator->common.lock);
	{
		i = 0;
		while (i < simulator->common.number_of_philosophers)
		{
			philo = &simulator->philos[i];
			if (pthread_create(&philo->thread_id, NULL, philo_do, philo) < 0)
			{
				simulator->common.done = 1;
				simulator->common.exit_status = EXIT_FAILURE;
				break ;
			}
			++i;
		}
		gettimeofday(&simulator->common.start_time, NULL);
	}
	pthread_mutex_unlock(&simulator->common.lock);
	while (i > 0)
		pthread_join(simulator->philos[--i].thread_id, NULL);
	simulator->common.done = 1;
}

int	main(int argc, char *argv[])
{
	static struct s_simulator	simulator;

	if (initial(&simulator, argc, argv))
		return (EXIT_FAILURE);
	simulate(&simulator);
	finally(&simulator);
	return (simulator.common.exit_status);
}
