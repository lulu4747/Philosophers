/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:42 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/26 00:51:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	destroy_all(int n, pid_t *tab)
{
	while (--n > 0)
		kill(tab[n - 1], SIGKILL);
}

static int	processes(t_phi phi)
{
	pid_t	pid;
	pid_t	tab[200];

	while (++phi.id <= phi.param.np)
	{
		pid = fork();
		if (pid < 0)
		{
			destroy_all(phi.id, tab);
			return (1);
		}
		if (pid == 0)
			life(phi);
		if (pid != 0)
			tab[phi.id - 1] = pid;
	}
	sem_wait(phi.die);
	destroy_all(phi.id, tab);
	return (0);
}

int	philosophy(t_param	param)
{
	t_phi	phi;

	phi.id = 0;
	phi.forks = sem_open("forks", O_CREAT | O_EXCL, 0644, param.np);
	phi.abs = sem_open("abs", O_CREAT | O_EXCL, 0644, 1);
	phi.die = sem_open("die", O_CREAT | O_EXCL, 0644, 0);
	phi.param = param;
	gettimeofday(&phi.start, NULL);
	phi.eat = phi.start;
	return (processes(phi));
}
