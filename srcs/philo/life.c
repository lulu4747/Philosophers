#include "philo.h"

static int	think(t_phi **phi)
{
	struct timeval	now;
	int				ret;

	ret = abs_lock(phi);
	if (ret != 0)
		return (1);
	gettimeofday(&now, NULL);
	printf("%d %d is thinking\n", milliseconds(now), (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	return (0);
}

static int	waiting(t_phi **phi, int time, int mode)
{
	int	ret;

	usleep(500);
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
	return (time_diff((*phi)->eat, time));
}

static int	nap(t_phi **phi, int time)
{
	struct timeval	now;
	int				ret;

	ret = abs_lock(phi);
	if (ret != 0)
		return (1);
	gettimeofday(&now, NULL);
	printf("%d %d is sleeping\n", milliseconds(now), (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	while (ret == 0)
	{
		ret = waiting(phi, time, 1);
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
	printf("%d %d is eating\n", milliseconds((*phi)->eat), (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	(*phi)->nb_meal++;
	while (ret == 0)
	{
		ret = waiting(phi, time, 0);
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
		if (print_fork(&phi, 3) != 0)
			return (delone(&phi));
		pthread_mutex_unlock(phi->right);
		if (print_fork(&phi, 4) != 0)
			return (delone(&phi));
		if (nap(&phi, phi->params[TS]) == 1)
			return (delone(&phi));
		if (think(&phi) == 1)
			return (delone(&phi));
	}
	return (NULL);
}
