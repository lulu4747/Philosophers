/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:36:11 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 18:16:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	abs_lock(t_phi **phi)
{
	pthread_mutex_lock((*phi)->abs);
	if ((*phi)->closing)
	{
		pthread_mutex_unlock((*phi)->abs);
		return (1);
	}
	return (0);
}

pthread_mutex_t	*mtx_destroy(pthread_mutex_t *mtx)
{
	pthread_mutex_destroy(mtx);
	free(mtx);
	return (NULL);
}

pthread_mutex_t	*mtx_create(const pthread_mutexattr_t *restrict attr)
{
	pthread_mutex_t	*mtx;

	mtx = malloc(sizeof(pthread_mutex_t));
	if (!mtx)
		return (NULL);
	if (pthread_mutex_init(mtx, attr) != 0)
	{
		free(mtx);
		return (NULL);
	}
	return (mtx);
}
