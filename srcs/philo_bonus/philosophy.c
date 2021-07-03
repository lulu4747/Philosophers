/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:42 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 15:44:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	semaphores_init(t_phi *phi, t_param param)
{
	sem_unlink("prio");
	sem_unlink("forks");
	sem_unlink("abs");
	sem_unlink("death_print");
	sem_unlink("ne");
	if (!(param.np / 2))
		phi->prio = sem_open("prio", O_CREAT | O_EXCL, 0644, 1);
	else
		phi->prio = sem_open("prio", O_CREAT | O_EXCL, 0644, (param.np / 2));
	phi->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, param.np);
	phi->abs = sem_open("abs", O_CREAT | O_EXCL, 0644, 1);
	phi->death_print = sem_open("death_print", O_CREAT | O_EXCL, 0644, 1);
	if (param.ne != -1)
		phi->ne_sem = sem_open("ne", O_CREAT | O_EXCL, 0644, 0);
	else
		phi->ne_sem = NULL;
	return (0);
}

int	philosophy(t_param	param)
{
	struct timeval	start;
	t_phi			phi;

	phi.id = 0;
	phi.nb_meal = 0;
	phi.param = param;
	if (semaphores_init(&phi, param))
		return (1);
	gettimeofday(&start, NULL);
	phi.tte = 0;
	phi.tts = 0;
	phi.ttd = param.ttd;
	phi.start = milliseconds(start);
	return (processes(phi));
}
