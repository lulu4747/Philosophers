#include "philo.h"

void	*delone(t_phi **phi)
{
	free((*phi));
	return (NULL);
}

void	*death(t_phi *phi)
{
	t_phi	*first;
	t_phi	*next;

	first = phi;
	phi = phi->next;
	while (phi != NULL && phi != first)
	{
		next = phi->next;
		free(phi);
		phi = next;
	}
	free(first);
	return (NULL);
}