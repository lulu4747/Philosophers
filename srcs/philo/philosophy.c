#include "philo.h"

static t_phi	*mutexes_builder(int id, t_phi *prev, t_phi *phi)
{
	int	ret;

	ret = 0;
	if (id == 0)
	{
		if (pthread_mutex_init(&(phi->left), NULL) != 0)
			ret = 2;
		if (pthread_mutex_init(&(phi->abs), NULL) != 0)
			ret += 1;
		if (ret != 0)
		{		
			pthread_mutex_destroy(&(phi->right));
			if (ret == 1)
				pthread_mutex_destroy(&(phi->left));
			if (ret == 2)
				pthread_mutex_destroy(&(phi->abs));
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
	t_phi	*phi;

	phi = malloc(sizeof(t_phi));
	if (!phi)
		return (NULL);
	if (id == 0 || id + 1 < params[NP])
	{
		if (pthread_mutex_init(&(phi->right), NULL) != 0)
		{
			free(phi);
			return (NULL);
		}
	}
	phi->id = id + 1;
	phi->params = params;
	phi->state = 0;
	phi->health = 0;
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
			return (death(first));
		phi = phi->next;
	}
	phi->next = first;
	phi->right = first->left;
	return (first);
}

int	philosophy(int *params)
{
	int		i;
	t_phi	*phi;

	i = 0;
	phi = philosophers_builder(params);
	if (!phi)
	{
		free(params);
		return (1);
	}
	while (++i <= params[NP])
	{
		pthread_create(&(phi->tid), NULL, &life, (void *)phi);
		phi = phi->next;
	}
	while (--i > 0)
	{
		pthread_join(phi->tid, NULL);
		phi = phi->next;
	}
	death(phi);
	free(params);
	return (0);
}