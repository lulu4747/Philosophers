#include "philo.h"

void	*death(t_phi *first)
{
	t_phi	*phi;
	t_phi	*next;
	int		i;

	i = 1;
	pthread_mutex_destroy(&(first->right));
	phi = first->next;
	while (phi != NULL && phi != first)
	{
		next = phi->next;
		if (i != phi->params[NP])
			pthread_mutex_destroy(&(phi->right));
		free(phi);
		phi = next;
		i++;
	}
	free(phi);
	return (NULL);
}