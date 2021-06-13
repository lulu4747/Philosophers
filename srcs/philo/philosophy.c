#include "philo.h"

static t_phi	*mutexes_builder(int id, t_phi *prev, t_phi *phi)
{
	int				ret;
	pthread_mutex_t	mtx;

	ret = 0;
	if (id == 0)
	{
		if (pthread_mutex_init(&mtx, NULL) != 0)
			ret = 2;
		phi->left = &mtx;
		if (pthread_mutex_init(&mtx, NULL) != 0)
			ret += 1;
		phi->abs = &mtx;
		if (ret != 0)
		{		
			pthread_mutex_destroy(phi->right);
			if (ret == 1)
				pthread_mutex_destroy(&(*(phi->left)));
			if (ret == 2)
				pthread_mutex_destroy(&(*(phi->abs)));
			free(phi);
			return (NULL);
		}
	}
	else
	{
		phi->left = prev->right;
		phi->abs = prev->abs;
	}
	return (phi);
}

static t_phi	*birth(int *params, int id, t_phi *prev)
{
	t_phi			*phi;
	pthread_mutex_t	mtx;

	phi = malloc(sizeof(t_phi));
	if (!phi)
		return (NULL);
	if (id == 0 || id + 1 < params[NP])
	{
		if (pthread_mutex_init(&mtx, NULL) != 0)
		{
			free(phi);
			return (NULL);
		}
		phi->right = &mtx;
	}
	phi->id = id + 1;
	gettimeofday(&(phi->eat), NULL);
	phi->nb_meal = 0;
	phi->params = params;
	phi->state = 0;
	return (mutexes_builder(id, prev, phi));
}

static t_phi	*philosophers_builder(int *params)
{
	t_phi	*first;
	t_phi	*phi;
	int		i;

	i = 0;
	if (params[NP] > 0)
		first = birth(params, i, NULL);
	if (!first)
		return (NULL);
	phi = first;
	while (++i < params[NP])
	{
		phi->next = birth(params, i, phi);
		if (!(phi->next))
		{
			pthread_mutex_destroy(first->abs);
			return (death(first));
		}
		phi = phi->next;
	}
	phi->next = first;
	phi->right = first->left;
	return (first);
}

int	philosophy(int *params)
{
	int			i;
	t_phi		*phi;
	pthread_t	status_tid;

	i = 0;
	phi = philosophers_builder(params);
	if (!phi)
	{
		free(params);
		return (1);
	}
	pthread_create(&status_tid, NULL, &philosophers_status, (void *)(&phi));
	while (++i <= params[NP])
	{
		gettimeofday(&(phi->eat), NULL);
		pthread_create(&(phi->tid), NULL, &life, (void *)phi);
		phi = phi->next;
	}
	pthread_join(status_tid, NULL);
	free(params);
	return (0);
}