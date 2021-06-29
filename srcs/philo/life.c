/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:35:51 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/29 00:23:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	think(t_phi **phi)
{
	int				ret;

	ret = abs_lock(phi);
	if (ret != 0)
		return (1);
	printf("%d %d is thinking\n", ts_ms((*phi)->start), (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	return (0);
}

static int	waiting(t_phi **phi, struct timeval	timevl, int time, int mode)
{
	int	ret;

	usleep(10);
	ret = abs_lock(phi);
	if (ret != 0)
	{
		if (!mode)
		{
			pthread_mutex_unlock((*phi)->left);
			pthread_mutex_unlock((*phi)->right);
		}
		return (2);
	}
	pthread_mutex_unlock((*phi)->abs);
	return (time_diff(timevl, time));
}

static int	nap(t_phi **phi, int time)
{
	int				ret;
	struct timeval	timevl;

	gettimeofday(&timevl, NULL);
	ret = abs_lock(phi);
	if (ret != 0)
		return (1);
	printf("%d %d is sleeping\n", ts_ms((*phi)->start), (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	while (ret == 0)
	{
		ret = waiting(phi, timevl, time, 1);
		if (ret == 2)
			return (1);
	}
	return (0);
}

static int	eat(t_phi **phi, int time)
{
	int	ret;

	ret = abs_lock(phi);
	if (ret != 0)
	{
		pthread_mutex_unlock((*phi)->left);
		pthread_mutex_unlock((*phi)->right);
		return (1);
	}
	gettimeofday(&((*phi)->eat), NULL);
	printf("%d %d is eating\n", ts_ms((*phi)->start), (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	(*phi)->nb_meal++;
	while (ret == 0)
	{
		ret = waiting(phi, (*phi)->eat, time, 0);
		if (ret == 2)
			return (1);
	}
	return (0);
}

void	*life(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while (1)
	{
		if (fork_lock(&phi) != 0)
			return (delone(&phi));
		if (eat(&phi, phi->params[TE]) == 1)
			return (delone(&phi));
		pthread_mutex_unlock(phi->left);
		pthread_mutex_unlock(phi->right);
		if (nap(&phi, phi->params[TS]) == 1)
			return (delone(&phi));
		if (think(&phi) == 1)
			return (delone(&phi));
	}
	return (NULL);
}
