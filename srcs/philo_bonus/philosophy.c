/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:42 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/27 23:05:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	destroy(t_phi phi)
{
	int	tmp;

	tmp = phi.id;
	while (--tmp >= 0)
		sem_post(phi.die);
	while (tmp++ < phi.id)
		waitpid(0, NULL, 0);
	sem_close(phi.forks);
	sem_close(phi.abs);
	sem_close(phi.death_print);
	sem_close(phi.die);
	if (phi.ne_sem)
		sem_close(phi.ne_sem);
}

static int	meals_counter(t_phi phi)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		destroy(phi);
		return (1);
	}
	if (pid == 0)
	{
		phi.id = 0;
		pthread_create(&(phi.tid_end), NULL, &status_end, (void *)(&phi));
		phi.ntrd++;
		while (!phi.closing && --phi.param.np >= 0)
			sem_wait(phi.ne_sem);
		if (!phi.closing)
			sem_post(phi.die);
		pthread_join(phi.tid_end, NULL);
		sem_wait(phi.abs);
		clean_exit(&phi);
	}
	return (0);
}

static int	processes(t_phi phi)
{
	pid_t	pid;

	while (++phi.id <= phi.param.np)
	{
		pid = fork();
		if (pid < 0)
		{
			destroy(phi);
			return (1);
		}
		if (pid == 0)
			life(&phi);
		if (phi.param.ne != -1 && phi.id == phi.param.np)
		{
			if (meals_counter(phi))
				return (1);
		}
	}
	waitpid(0, NULL, 0);
	if (phi.param.ne == -1)
		phi.id--;
	destroy(phi);
	return (0);
}

static int	semaphores_init(t_phi *phi)
{
	sem_unlink("forks");
	sem_unlink("abs");
	sem_unlink("death_print");
	sem_unlink("die");
	sem_unlink("ne");
	phi->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, phi->param.np);
	phi->abs = sem_open("abs", O_CREAT | O_EXCL, 0644, 1);
	phi->death_print = sem_open("death_print", O_CREAT | O_EXCL, 0644, 1);
	phi->die = sem_open("die", O_CREAT | O_EXCL, 0644, 0);
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
	phi.ntrd = 0;
	phi.closing = 0;
	if (semaphores_init(&phi))
		return (1);
	gettimeofday(&phi.start, NULL);
	phi.eat = phi.start;
	return (processes(phi));
}
