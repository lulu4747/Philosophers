#include "philo.h"

static int	think(t_phi **phi)
{
	struct timeval	now;
	int				ret;

	ret = abs_lock(phi);
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

	ret = abs_lock(phi);
	if (ret != 0)
		return (1);
	gettimeofday(&now, NULL);
	printf("%ld %d is sleeping\n", now.tv_usec, (*phi)->id);
	pthread_mutex_unlock((*phi)->abs);
	while (ret == 0)
	{
		usleep(500);
		ret = abs_lock(phi);
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

	ret = abs_lock(phi);
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
		usleep(500);
		ret = abs_lock(phi);
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

void	*life(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	usleep(1000 * (phi->params[NP] - phi->id));
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