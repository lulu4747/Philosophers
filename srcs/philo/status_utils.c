/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:36:59 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/21 19:37:01 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*end(t_status **status, t_phi **phi, int bl)
{
	pthread_mutex_t	*abs;

	abs = (*status)->abs;
	pthread_mutex_lock((*status)->state);
	if (bl == 1)
		printf("%d %d died\n", ts_ms((*phi)->start), (*phi)->id);
	(*status)->abs = mtx_destroy((*status)->abs);
	pthread_mutex_unlock((*status)->state);
	return (NULL);
}

void	*philosophers_status(void *arg)
{
	t_status	**status;
	t_phi		*phi;
	int			i;

	i = 0;
	status = (t_status **)arg;
	phi = (*status)->phi;
	while (1)
	{
		if (time_diff(phi->eat, phi->params[TD]))
			return (end(status, &phi, 1));
		if (phi->params[NE] != -1)
		{
			if (phi->nb_meal < phi->params[NE])
				i = 0;
			else
				i++;
			if (i >= phi->params[NP])
				return (end(status, &phi, 0));
		}
		phi = phi->next;
	}
	return (NULL);
}

t_status	*status_clean(t_status *status)
{
	if (status->abs != NULL)
		status->abs = mtx_destroy(status->abs);
	if (status->state != NULL)
		status->state = mtx_destroy(status->state);
	if (status->frk != NULL)
		frk_free(status->frk);
	free(status);
	return (NULL);
}
