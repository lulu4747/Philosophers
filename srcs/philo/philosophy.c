#include "philo.h"

static t_phi	*mutexes_builder(int id, t_phi *prev, t_phi *phi)
{
	if (id == 0)
	{
		phi->abs = mtx_create(NULL);
		phi->left = mtx_create(NULL);
		if (!phi->left || !phi->abs)
		{		
			phi->right = mtx_destroy(phi->right);
			if (phi->abs != NULL)
				phi->abs = mtx_destroy(phi->abs);
			if (phi->left != NULL)
				phi->left = mtx_destroy(phi->left);
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

	phi = malloc(sizeof(t_phi));
	if (!phi)
		return (NULL);
	if (id == 0 || id + 1 < params[NP])
	{
		phi->right = mtx_create(NULL);
		if (!phi->right)
		{
			free(phi);
			return (NULL);
		}
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
			return (death(first));
		phi = phi->next;
	}
	phi->next = first;
	if (i != 0)
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