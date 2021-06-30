/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:35:34 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/21 19:35:36 by lfourage         ###   ########lyon.fr   */
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
		free(phi);
		phi = next;
	}
	free(first);
	return (NULL);
}
