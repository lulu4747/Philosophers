/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frk_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:35:42 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/21 19:35:44 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_fork(t_phi **phi, int type)
{
	int				ret;

	ret = abs_lock(phi);
	if (ret != 0)
	{
		pthread_mutex_unlock((*phi)->left);
		pthread_mutex_unlock((*phi)->right);
		return (1);
	}
	ret = ts_ms((*phi)->start);
	if (type <= 2)
		printf("%d %d has taken a fork\n", ret, (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	return (0);
}

int	fork_lock(t_phi **phi)
{
	if (!((*phi)->id % 2))
		pthread_mutex_lock((*phi)->right);
	else
		pthread_mutex_lock((*phi)->left);
	if (print_fork(phi, 1) != 0)
		return (1);
	if (!((*phi)->id % 2))
		pthread_mutex_lock((*phi)->left);
	else
		pthread_mutex_lock((*phi)->right);
	if (print_fork(phi, 2) != 0)
		return (1);
	return (0);
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
