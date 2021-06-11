#include "philo.h"

t_phi	*death(t_phi *first)
{
	t_phi	*phi;
	t_phi	*next;

	if (first->right)
		pthread_mutex_destroy(first->right);
	if (first->abs)
		pthread_mutex_destroy(first->abs);
	phi = first->next;
	while (phi != NULL && phi != first)
	{
		next = phi->next;
		if (phi->right)
			pthread_mutex_destroy(phi->right);
		free(phi);
		phi = next;
	}
	free(phi);
	return (NULL);
}