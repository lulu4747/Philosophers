/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:35:34 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 17:37:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death(t_phi *phi)
{
	t_phi	*first;
	t_phi	*next;

	first = phi;
	phi = phi->next;
	while (phi != NULL && phi != first)
	{
		next = phi->next;
		phi->eating = mtx_destroy(phi->eating);
		free(phi);
		phi = next;
	}
	first->eating = mtx_destroy(first->eating);
	free(first);
	return (NULL);
}
