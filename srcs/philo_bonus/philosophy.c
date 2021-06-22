/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:42 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/21 19:37:44 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philosophy(int *params)
{
	sem_t	*sem_forks;

	forks = malloc(sizeof(sem_t));
	if (!forks)
	{
		free(params);
		return (1);
	}
	sem_forks = sem_open("forks", O_CREAT, 0644, params[NP]);
	free(params);
	return (0);
}
