/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:42 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/26 02:03:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	destroy(int n, sem_t *sem, pid_t *tab)
{
	usleep(100 * n);
	while (--n > 0)
		kill(tab[n - 1], SIGKILL);
	sem_unlink("forks");
	sem_unlink("abs");
	sem_unlink("die");
	if (sem != NULL)
		sem_unlink("ne");
}

static int	meals_counter(t_phi phi, pid_t *tab)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		destroy(phi.id, phi.ne_sem, tab);
		return (1);
	}
	if (pid == 0)
	{
		phi.abs = sem_open("abs", O_RDWR);
		phi.die = sem_open("die", O_RDWR);
		phi.ne_sem = sem_open("ne", O_RDWR);
		while (--phi.param.np >= 0)
			sem_wait(phi.ne_sem);
		sem_wait(phi.abs);
		sem_post(phi.die);
		sem_unlink("die");
		sem_unlink("ne");
		exit(EXIT_SUCCESS);
	}
	return (0);
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
			destroy(phi.id, phi.ne_sem, tab);
			return (1);
		}
		if (pid == 0)
			life(&phi);
		if (pid != 0)
			tab[phi.id - 1] = pid;
		if (phi.id == 1 && phi.param.ne != -1)
		{
			if (meals_counter(phi, tab))
				return (1);
		}
	}
	sem_wait(phi.die);
	destroy(phi.id, phi.ne_sem, tab);
	return (0);
}

int	philosophy(t_param	param)
{
	t_phi	phi;

	phi.id = 0;
	phi.nb_meal = 0;
	phi.forks = sem_open("forks", O_CREAT | O_EXCL, 0644, param.np);
	phi.abs = sem_open("abs", O_CREAT | O_EXCL, 0644, 1);
	phi.die = sem_open("die", O_CREAT | O_EXCL, 0644, 0);
	if (phi.param.ne != -1)
		phi.ne_sem = sem_open("ne", O_CREAT | O_EXCL, 0644, 0);
	else
		phi.ne_sem = NULL;
	phi.param = param;
	gettimeofday(&phi.start, NULL);
	phi.eat = phi.start;
	return (processes(phi));
}
