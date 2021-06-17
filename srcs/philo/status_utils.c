#include "philo.h"

int	time_diff(struct timeval diff, int n)
{
	struct timeval	now;
	int				ms_diff;

	gettimeofday(&now, NULL);
	ms_diff = (int)(now.tv_usec - diff.tv_usec);
	if (ms_diff >= n)
		return (1);
	return (0);
}

static void	*end(t_phi **phi, int bl)
{
	pthread_mutex_t	*abs;
	struct timeval	now;

	abs = (*phi)->abs;
	pthread_mutex_lock(abs);
	if (bl == 1)
	{
		gettimeofday(&now, NULL);
		printf("%ld %d died\n", now.tv_usec, (*phi)->id);
	}
	while (!((*phi)->health))
	{
		(*phi)->health = 1;
		*phi = (*phi)->next;
	}
	pthread_mutex_unlock(abs);
	return (NULL);
}

void	*philosophers_status(void *arg)
{
	t_phi			**phi;
	int				i;

	i = 0;
	phi = (t_phi **)arg;
	while (*phi)
	{
		if (time_diff((*phi)->eat, (*phi)->params[TD]) == 1)
			return (end(phi, 1));
		if ((*phi)->state == 0)
			i = 0;
		else
		{
			if ((*phi)->params[NE] != -1 && (*phi)->nb_meal >= (*phi)->params[NE])
				(*phi)->state = 1;
			i++;
		}
		if ((*phi)->params[NE] != -1 && i >= (*phi)->params[NP])
			return(end(phi, 0));
		*phi = (*phi)->next;
	}
	return (NULL);
}