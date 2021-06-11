#include "philo.h"

static t_phi	*mutexes_builder(int *params, int id, t_phi *prev, t_phi *phi)
{
	if (id == 0)
	{
		if (pthread_mutex_init(&(phi->left)) != 0)
		{
			free(phi);
			return (NULL)
		}
		if (pthread_mutex_init(&(phi->abs)) != 0)
		{
			pthread_mutex_destroy(phi->left);
			free(phi);
			return (NULL)
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

	phi = malloc(sizeof(t_phi))
	if (!phi)
		return (NULL);
	if (id < params[NP])
	{
		if (pthread_mutex_init(&(phi->right)) != 0)
		{
			free(phi);
			return (NULL);
		}
	}
	phi->id = id + 1;
	phi->params = params;
	phi->nm = 0;
	phi->state = 0;
	phi->health = 0;
	return (mutexes_builder(params, id, prev, phi));
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
	t_phi	*phi;

	phi = philosophers_builder(params);
	if (!phi)
	{
		free(params);
		return (1);
	}
	free(params);
	return (0);
}