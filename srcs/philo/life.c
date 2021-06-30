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

	ret = abs_lock(phi);
	if (ret != 0)
		return (1);
	printf("%d %d is sleeping\n", ts_ms((*phi)->start), (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	usleep((*phi)->tts);
	return (0);
}

static int	eat(t_phi **phi)
{
	int	ret;
	int	tmp;

	ret = abs_lock(phi);
	if (ret != 0)
	{
		pthread_mutex_unlock((*phi)->left);
		pthread_mutex_unlock((*phi)->right);
		return (1);
	}
	tmp = ts_ms((*phi)->start);
	(*phi)->ttd = tmp + (*phi)->params[TD];
	printf("%d %d is eating\n", tmp, (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	(*phi)->nb_meal++;
	usleep((*phi)->tte);
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
