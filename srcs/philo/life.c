/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:35:51 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 18:20:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	think(t_phi **phi)
{
	int	ret;

	ret = abs_lock(phi);
	if (ret != 0)
		return (1);
	printf("%d %d is thinking\n", ts_ms((*phi)->start), (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	usleep(250);
	return (0);
}

static int	nap(t_phi **phi)
{
	int	ret;
	int	tmp;

	ret = abs_lock(phi);
	if (ret != 0)
		return (1);
	tmp = ts_ms((*phi)->start);
	(*phi)->tts = tmp + (*phi)->params[TS];
	printf("%d %d is sleeping\n", tmp, (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	while (!(time_diff((*phi)->tts, (*phi)->start)))
		usleep(250);
	return (0);
}

static int	eat(t_phi **phi)
{
	int	ret;
	int	tmp;

	pthread_mutex_lock((*phi)->eating);
	ret = abs_lock(phi);
	if (ret != 0)
	{
		pthread_mutex_unlock((*phi)->left);
		pthread_mutex_unlock((*phi)->right);
		return (1);
	}
	tmp = ts_ms((*phi)->start);
	(*phi)->ttd = tmp + (*phi)->params[TD];
	pthread_mutex_unlock((*phi)->eating);
	(*phi)->tte = tmp + (*phi)->params[TE];
	printf("%d %d is eating\n", tmp, (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	while (!(time_diff((*phi)->tte, (*phi)->start)))
		usleep(250);
	(*phi)->nb_meal++;
	return (0);
}

void	*life(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while (1)
	{
		if (fork_lock(&phi) != 0)
			return (NULL);
		if (eat(&phi) == 1)
			return (NULL);
		pthread_mutex_unlock(phi->left);
		pthread_mutex_unlock(phi->right);
		if (nap(&phi) == 1)
			return (NULL);
		if (think(&phi) == 1)
			return (NULL);
	}
	return (NULL);
}
