#include "philo.h"

int	print_fork(t_phi **phi, int type)
{
	struct timeval	now;
	int				ret;

	ret = abs_lock(phi);
	if (ret != 0)
	{
		if (type <= 2)
			pthread_mutex_unlock((*phi)->left);
		if (type == 2 || type == 3)
			pthread_mutex_unlock((*phi)->right);
		return (1);
	}
	gettimeofday(&now, NULL);
	if (type <= 2)
		printf("%d %d has taken a fork\n", milliseconds(now), (*phi)->id);
	else
		printf("%d %d has put a fork back on the table\n", milliseconds(now), (*phi)->id);
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
	first->mtx = mtx_destroy(first->mtx);
	frk = frk->next;
	while (frk != NULL && frk != first)
	{
		next = frk->next;
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