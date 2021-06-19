#include "philo.h"

int	milliseconds(struct timeval time)
{
	int	ret;

	ret = (int)(time.tv_sec * 1000);
	ret += (int)(time.tv_usec / 1000);
	return (ret);
}

int	time_diff(struct timeval diff, int n)
{
	struct timeval	now;
	int				ms_diff;

	gettimeofday(&now, NULL);
	ms_diff = milliseconds(now) - milliseconds(diff);
	if (ms_diff >= n)
		return (1);
	return (0);
}

static void	*end(t_status **status, t_phi **phi, int bl)
{
	pthread_mutex_t	*abs;
	struct timeval	now;

	abs = (*status)->abs;
	pthread_mutex_lock(abs);
	if (bl == 1)
	{
		gettimeofday(&now, NULL);
		printf("%d %d died\n", milliseconds(now), (*phi)->id);
	}
	pthread_mutex_lock((*status)->state);
	(*status)->closing = 1;
	pthread_mutex_unlock((*status)->state);
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
	t_status	**status;
	t_phi		*phi;
	int			i;

	i = 0;
	status = (t_status **)arg;
	phi = (*status)->phi;
	while (1)
	{
		if (time_diff(phi->eat, phi->params[TD]) == 1)
			return (end(status, &phi, 1));
		if (phi->params[NE] != -1)
		{
			if (phi->nb_meal < phi->params[NE])
				i = 0;
			else 
				i++;
			if (i >= phi->params[NP])
				return(end(status, &phi, 0));
		}
		phi = phi->next;
	}
	return (NULL);
}

t_status	*status_clean(t_status *status)
{
	if (status->abs != NULL)
		status->abs = mtx_destroy(status->abs);
	if (status->state != NULL)
		status->state = mtx_destroy(status->state);
	if (status->frk != NULL)
		frk_free(status->frk);
	free(status);
	return (NULL);
}