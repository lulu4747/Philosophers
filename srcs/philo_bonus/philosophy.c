/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:42 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/29 09:31:16 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	destroy(t_phi phi, pid_t *tab, int r)
{
	phi.id--;
	while (--phi.id >= 0)
		kill(tab[phi.id], SIGKILL);
	sem_unlink("prio");
	sem_unlink("forks");
	sem_unlink("abs");
	sem_unlink("death_print");
	sem_unlink("ne");
	sem_close(phi.prio);
	sem_close(phi.forks);
	sem_close(phi.abs);
	sem_close(phi.death_print);
	if (phi.ne_sem)
		sem_close(phi.ne_sem);
	return (r);
}

static int	meals_counter(t_phi phi, int *pid, pid_t *tab)
{
	*pid = fork();
	if (*pid < 0)
		return (destroy(phi, tab, 1));
	if (*pid == 0)
	{
		phi.id = 0;
		while (--phi.param.np >= 0)
			sem_wait(phi.ne_sem);
		sem_wait(phi.abs);
		clean_exit(&phi);
	}
	return (0);
}

static int	processes(t_phi phi)
{
	pid_t	pid;
	pid_t	tab[201];

	while (++phi.id <= phi.param.np)
	{
		pid = fork();
		if (pid < 0)
			return (destroy(phi, tab, 1));
		if (pid == 0)
			life(&phi);
		else
			tab[phi.id - 1] = pid;
		if (phi.param.ne != -1 && phi.id == phi.param.np)
		{
			if (meals_counter(phi, &pid, tab))
				return (1);
			tab[phi.id] = pid;
		}
	}
	waitpid(0, NULL, 0);
	if (phi.param.ne == -1)
		phi.id--;
	return (destroy(phi, tab, 0));
}

static int	semaphores_init(t_phi *phi)
{
	sem_unlink("prio");
	sem_unlink("forks");
	sem_unlink("abs");
	sem_unlink("death_print");
	sem_unlink("ne");
	phi->prio = sem_open("prio", O_CREAT | O_EXCL, 0644, (phi->param.np / 2));
	phi->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, phi->param.np);
	phi->abs = sem_open("abs", O_CREAT | O_EXCL, 0644, 1);
	phi->death_print = sem_open("death_print", O_CREAT | O_EXCL, 0644, 1);
	if (phi->param.ne != -1)
		phi->ne_sem = sem_open("ne", O_CREAT | O_EXCL, 0644, 0);
	else
		phi->ne_sem = NULL;
	return (0);
}

int	philosophy(t_param	param)
{
	t_phi	phi;

	phi.id = 0;
	phi.nb_meal = 0;
	phi.param = param;
	if (semaphores_init(&phi))
		return (1);
	gettimeofday(&phi.start, NULL);
	phi.eat = phi.start;
	return (processes(phi));
}
