/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:36:49 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/21 19:36:52 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_phi	*birth(int *params, int id, t_frk *frk, pthread_mutex_t *abs)
{
	t_phi			*phi;

	phi = malloc(sizeof(t_phi));
	if (!phi)
		return (NULL);
	phi->abs = abs;
	phi->left = frk->mtx;
	phi->right = frk->next->mtx;
	phi->id = id + 1;
	phi->nb_meal = 0;
	gettimeofday(&(phi->eat), NULL);
	phi->params = params;
	phi->health = 0;
	return (phi);
}

static t_phi	*philosophers_builder(int *p, t_frk *frk, pthread_mutex_t *abs)
{
	t_phi	*first;
	t_phi	*phi;
	int		i;

	i = 0;
	first = birth(p, i, frk, abs);
	if (!first)
		return (NULL);
	phi = first;
	while (++i < p[NP])
	{
		frk = frk->next;
		phi->next = birth(p, i, frk, abs);
		if (!(phi->next))
			return (death(first));
		phi->next->prev = phi;
		phi = phi->next;
	}
	phi->next = first;
	first->prev = phi;
	phi->right = first->left;
	return (first);
}

t_status	*status_builder(int *params)
{
	t_status	*status;

	status = malloc(sizeof(t_status));
	if (!status)
	{
		free(params);
		return (NULL);
	}
	status->closing = 0;
	status->state = NULL;
	status->phi = NULL;
	status->frk = NULL;
	status->abs = mtx_create(NULL);
	if (!status->abs)
		return (status_clean(status));
	status->state = mtx_create(NULL);
	if (!status->abs)
		return (status_clean(status));
	status->frk = frk_builder(params[NP]);
	if (!status->frk)
		return (status_clean(status));
	status->phi = philosophers_builder(params, status->frk, status->abs);
	if (!status->phi)
		return (status_clean(status));
	return (status);
}

static void	phi_launcher(t_status *status, t_phi *phi, int *params)
{
	int	i;

	i = 0;
	while (++i <= params[NP] && !status->closing)
	{
		pthread_mutex_lock(status->state);
		if (!status->closing)
		{
			pthread_create(&(phi->tid), NULL, &life, (void *)phi);
			pthread_detach(phi->tid);
			phi = phi->next;
		}
		pthread_mutex_unlock(status->state);
	}
	if (i < params[NP])
	{
		status->phi = phi;
		while (++i <= params[NP])
			phi = phi->next;
		phi->next = NULL;
		death(status->phi);
	}
}

int	philosophy(int *params)
{
	t_status		*status;

	status = status_builder(params);
	if (!status)
	{
		free(params);
		return (1);
	}
	pthread_create(&status->tid, NULL, &philosophers_status, (void *)(&status));
	phi_launcher(status, status->phi, params);
	pthread_join(status->tid, NULL);
	usleep(10000 * params[NP]);
	free(params);
	status = status_clean(status);
	return (0);
}
