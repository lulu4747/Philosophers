/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:36:49 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 13:50:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	phi_launcher(t_phi *phi, int *params)
{
	int	i;

	i = 0;
	while (++i <= params[NP])
	{
		pthread_create(&(phi->tid), NULL, &life, (void *)phi);
		phi = phi->next;
	}
}

int	philosophy(int *params)
{
	t_status		*status;
	t_phi			*phi;
	int				i;

	i = -1;
	status = NULL;
	status = status_builder(params, status);
	if (!status)
	{
		free(params);
		return (1);
	}
	phi = status->phi;
	phi_launcher(phi, params);
	pthread_create(&status->tid, NULL, &philosophers_status, (void *)(&status));
	pthread_join(status->tid, NULL);
	while (++i < params[NP])
	{
		pthread_join(phi->tid, NULL);
		phi = phi->next;
	}
	free(params);
	status = status_clean(status);
	return (0);
}
