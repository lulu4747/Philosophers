/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frk_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:35:42 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 18:16:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_fork(t_phi **phi)
{
	int	ret;

	ret = abs_lock(phi);
	if (ret != 0)
	{
		pthread_mutex_unlock((*phi)->left);
		pthread_mutex_unlock((*phi)->right);
		return (1);
	}
	printf("%d %d has taken a fork\n", ts_ms((*phi)->start), (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	return (0);
}

int	fork_lock(t_phi **phi)
{
	if ((*phi)->even)
		pthread_mutex_lock((*phi)->right);
	else
		pthread_mutex_lock((*phi)->left);
	if (print_fork(phi))
		return (1);
	if ((*phi)->even)
	{
		if (!(*phi)->left)
			return (1);
		pthread_mutex_lock((*phi)->left);
	}
	else
		pthread_mutex_lock((*phi)->right);
	return (print_fork(phi));
}

void	frk_free(t_frk *frk)
{
	t_frk	*first;
	t_frk	*next;

	first = frk;
	if (first->mtx != NULL)
		first->mtx = mtx_destroy(first->mtx);
	frk = frk->next;
	while (frk != NULL && frk != first)
	{
		next = frk->next;
		if (frk->mtx != NULL)
			frk->mtx = mtx_destroy(frk->mtx);
		free(frk);
		frk = next;
	}
	free(first);
}

static t_frk	*frk_element(const pthread_mutexattr_t *restrict attr)
{
	t_frk	*frk;

	frk = malloc(sizeof(t_frk));
	if (!frk)
		return (NULL);
	frk->mtx = mtx_create(attr);
	if (!frk->mtx)
	{
		free(frk);
		return (NULL);
	}
	frk->next = NULL;
	return (frk);
}

t_frk	*frk_builder(int n)
{
	t_frk	*first;
	t_frk	*frk;

	first = frk_element(NULL);
	if (!first)
		return (NULL);
	frk = first;
	while (--n > 0)
	{
		frk->next = frk_element(NULL);
		if (!frk->next)
		{
			frk_free(first);
			return (NULL);
		}
		frk = frk->next;
	}
	frk->next = first;
	return (first);
}
