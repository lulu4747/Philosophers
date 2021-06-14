#include "philo.h"

void	*death(t_phi *first)
{
	t_phi	*phi;
	t_phi	*next;

	if (first->abs != NULL)
		first->abs = mtx_destroy(first->abs);
	if (first->right != NULL)
		first->right = mtx_destroy(first->right);
	phi = first;
	while (phi != NULL)
	{
		next = phi->next;
		if (phi->right != NULL)
			phi->right = mtx_destroy(phi->right);
		free(phi);
		phi = next;
	}
	return (NULL);
}