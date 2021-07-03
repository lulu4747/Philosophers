/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 12:26:04 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 17:50:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_phi	*birth(int *params, int id, t_frk *frk, pthread_mutex_t *abs)
{
	t_phi			*phi;

	phi = malloc(sizeof(t_phi));
	if (!phi)
		return (NULL);
	phi->eating = mtx_create(NULL);
	if (!phi->eating)
	{
		free(phi);
		return (NULL);
	}
	phi->abs = abs;
	phi->left = frk->mtx;
	phi->right = frk->next->mtx;
	phi->id = id + 1;
	phi->even = phi->id % 2;
	phi->nb_meal = 0;
	phi->closing = 0;
	phi->params = params;
	phi->tte = 0;
	phi->tts = 0;
	phi->ttd = params[TD];
	return (phi);
}

static int	get_start(void)
{
	struct timeval	start;

	gettimeofday(&(start), NULL);
	return (milliseconds(start));
}

static t_phi	*philosophers_builder(int *p, t_frk *frk,
	pthread_mutex_t *abs)
{
	t_phi	*first;
	t_phi	*phi;
	int		i;

	i = 0;
	first = birth(p, i, frk, abs);
	if (!first)
		return (NULL);
	first->start = get_start();
	phi = first;
	while (++i < p[NP])
	{
		frk = frk->next;
		phi->next = birth(p, i, frk, abs);
		if (!(phi->next))
			return (death(first));
		phi = phi->next;
		phi->start = first->start;
	}
	phi->next = first;
	phi->right = first->left;
	return (first);
}

t_status	*status_builder(int *params, t_status *status)
{
	status = malloc(sizeof(t_status));
	if (!status)
	{
		free(params);
		return (NULL);
	}
	status->ts = 0;
	status->phi = NULL;
	status->frk = NULL;
	status->abs = mtx_create(NULL);
	if (!status->abs)
		return (status_clean(status));
	status->frk = frk_builder(params[NP]);
	if (!status->frk)
		return (status_clean(status));
	status->phi = philosophers_builder(params, status->frk,
			status->abs);
	if (!status->phi)
		return (status_clean(status));
	if (params[NP] == 1)
		status->phi->left = NULL;
	return (status);
}
