#include "philo.h"

static t_phi	*eat(t_phi *phi, int time)
{
	gettimeofday(&(phi->eat), NULL);
	pthread_mutex_lock(&(phi->abs));
	printf("%d %d is eating\n", phi->eat->tv_usec, phi->id);
	pthread_mutex_unlock(&(phi->abs));
	while (!(check_status(phi)))
		gettimeofday(&(phi->tmp), NULL);
}

void	*life(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	gettimeofday(&(phi->eat), NULL);
	while (phi->health == 0)
	{
		pthread_mutex_lock(&(phi->left));
		pthread_mutex_lock(&(phi->right));
		phi = eat(phi, params[TE]);
		pthread_mutex_unlock(&(phi->left));
		pthread_mutex_unlock(&(phi->right));
	}
	return (NULL);
}