#include "philo.h"

static int	think(t_phi **phi)
{
	struct timeval	now;
	int				ret;

	ret = pthread_mutex_lock((*phi)->abs);
	if (ret != 0)
		return (1);
	gettimeofday(&now, NULL);
	printf("%ld %d is thinking\n", now.tv_usec, (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	return (0);
}

static int	nap(t_phi **phi, int time)
{
	struct timeval	now;
	int				ret;

	ret = pthread_mutex_lock((*phi)->abs);
	if (ret != 0)
		return (1);
	gettimeofday(&now, NULL);
	printf("%ld %d is sleeping\n", now.tv_usec, (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	while (ret == 0)
	{
		ret = pthread_mutex_lock((*phi)->abs);
		if (ret != 0)
			return (1);
		pthread_mutex_unlock((*phi)->abs);
		ret = time_diff(now, time);
	}
	return (0);
}

static int	eat(t_phi **phi, int time)
{
	int	ret;

	ret = pthread_mutex_lock((*phi)->abs);
	if (ret != 0)
	{
		pthread_mutex_unlock((*phi)->left);
		pthread_mutex_unlock((*phi)->right);
		return (1);
	}
	gettimeofday(&((*phi)->eat), NULL);
	printf("%ld %d is eating\n", (*phi)->eat.tv_usec, (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	(*phi)->nb_meal++;
	while (ret == 0)
	{
		ret = pthread_mutex_lock((*phi)->abs);
		if (ret != 0)
		{
			pthread_mutex_unlock((*phi)->left);
			pthread_mutex_unlock((*phi)->right);
			return (1);
		}
		pthread_mutex_unlock((*phi)->abs);
		ret = time_diff((*phi)->eat, time);
	}
	return (0);
}

static int	print_fork(t_phi *phi, int type)
{
	struct timeval	now;
	int				ret;

	ret = pthread_mutex_lock(phi->abs);
	if (ret != 0)
	{
		if (type <= 2)
			pthread_mutex_unlock(phi->left);
		if (type == 2 || type == 3)
			pthread_mutex_unlock(phi->right);
		return (1);
	}
	gettimeofday(&now, NULL);
	if (type <= 2)
		printf("%ld %d has taken a fork\n", now.tv_usec, phi->id);
	else
		printf("%ld %d has put a fork back on the table\n", now.tv_usec, phi->id);
	pthread_mutex_unlock(phi->abs);
	return (0);
}

void	*life(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while (1)
	{
		pthread_mutex_lock(phi->left);
		if (print_fork(phi, 1) != 0)
			return (NULL);
		pthread_mutex_lock(phi->right);
		if (print_fork(phi, 2) != 0)
			return (NULL);
		if (eat(&phi, phi->params[TE]) == 1)
			return (NULL);
		pthread_mutex_unlock(phi->left);
		if (print_fork(phi, 3) != 0)
			return (NULL);
		pthread_mutex_unlock(phi->right);
		if (print_fork(phi, 4) != 0)
			return (NULL);
		if (nap(&phi, phi->params[TS]) == 1)
			return (NULL);
		if (think(&phi) == 1)
			return (NULL);
	}
	return (NULL);
}