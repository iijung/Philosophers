/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:01:16 by minjungk          #+#    #+#             */
/*   Updated: 2023/03/11 18:24:37 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

extern int	philo_do(void *param);

extern int	ft_sem_unlink(const char *prefix, int id)
{
	char	name[30];
	int		i;
	int		prefix_len;

	prefix_len = 0;
	while (prefix && prefix[prefix_len] && prefix_len < 10)
		++prefix_len;
	memset(name, 0, sizeof(name));
	ft_memcpy(name, prefix, prefix_len);
	i = prefix_len;
	if (id == 0)
		name[i] = '0';
	while (id > 0)
	{
		name[i++] = "0123456789"[id % 10];
		id /= 10;
	}
	return (sem_unlink(name));
}

extern sem_t	*ft_sem_open(const char *prefix, int id)
{
	char	name[30];
	int		i;
	int		prefix_len;

	prefix_len = 0;
	while (prefix && prefix[prefix_len] && prefix_len < 10)
		++prefix_len;
	memset(name, 0, sizeof(name));
	ft_memcpy(name, prefix, prefix_len);
	i = prefix_len;
	if (id == 0)
		name[i] = '0';
	while (id > 0)
	{
		name[i++] = "0123456789"[id % 10];
		id /= 10;
	}
	return (sem_open(name, O_CREAT | O_EXCL, 0644, 1));
}

static void	main_process(struct s_simulator *simulator)
{
	int	i;
	int	pid;
	int	status;

	i = 0;
	while (i < simulator->common.number_of_philosophers)
	{
		pid = waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == EXIT_FAILURE)
		{
			kill(-pid, SIGINT);
			break ;
		}
		++i;
	}
}

static int	simulate(struct s_simulator *simulator)
{
	struct s_common *const	common = &simulator->common;
	int						i;

	sem_wait(common->lock);
	i = 0;
	while (i < common->number_of_philosophers)
	{
		if (fork() == 0)
		{
			common->exit_status = philo_do(&simulator->philos[i]);
			return (simulator->philos[i].process_num);
		}
		++i;
	}
	sem_post(common->lock);
	main_process(simulator);
	return (0);
}

int	main(int argc, char *argv[])
{
	static struct s_simulator	simulator;

	if (initial(&simulator, argc, argv))
		return (EXIT_FAILURE);
	finally(&simulator, simulate(&simulator));
	return (simulator.common.exit_status);
}
