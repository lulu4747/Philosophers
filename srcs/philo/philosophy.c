#include "philo.h"

static t_phi	*birth(int *params, int id, t_frk *frk, pthread_mutex_t *abs)
{
	t_phi			*phi;

	phi = malloc(sizeof(t_phi));
	if (!phi)
		return (NULL);
	phi->abs = abs;
	phi->left = frk->mtx;
	phi->right = frk->next->mtx;
	phi->id = id + 1;
	phi->nb_meal = 0;
	gettimeofday(&(phi->eat), NULL);
	phi->params = params;
	phi->state = 0;
	phi->health = 0;
	return (phi);
}

static t_phi	*philosophers_builder(int *params, t_frk *frk, pthread_mutex_t *abs)
{
	t_phi	*first;
	t_phi	*phi;
	int		i;

	i = 0;
	if (params[NP] > 0)
		first = birth(params, i, frk, abs);
	if (!first)
		return (NULL);
	phi = first;
	while (++i < params[NP])
	{
		frk = frk->next;
		phi->next = birth(params, i, frk, abs);
		if (!(phi->next))
			return (death(first));
		phi->next->prev = phi;
		phi = phi->next;
	}
	phi->next = first;
	first->prev = phi;
	phi->right = first->left;
	return (first);
}

int	philosophy(int *params)
{
	int				i;
	t_phi			*phi;
	pthread_t		status_tid;
	pthread_mutex_t	*abs;
	t_frk			*frk;

	i = 0;
	abs = mtx_create(NULL);
	if (!abs)
	{
		free(params);
		return (1);
	}
	frk = frk_builder(params[NP]);
	if (!frk)
	{
		abs = mtx_destroy(abs);
		free(params);
		return (1);
	}
	phi = philosophers_builder(params, frk, abs);
	if (!phi)
	{
		abs = mtx_destroy(abs);
		frk_free(frk);
		free(params);
		return (1);
	}
	pthread_create(&status_tid, NULL, &philosophers_status, (void *)(&phi));
	while (++i <= params[NP])
	{
		pthread_create(&(phi->tid), NULL, &life, (void *)phi);
		pthread_detach(phi->tid);
		phi = phi->next;
	}
	pthread_join(status_tid, NULL);
	usleep(100000 * params[NP]);
	free(params);
	abs = mtx_destroy(abs);
	frk_free(frk);
	return (0);
}