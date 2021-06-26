#include "philo_bonus.h"

void	*status_monitor(void *arg)
{
	int		i;
	t_phi	*phi;

	i = 0;
	phi = (t_phi *)arg;
	while (1)
	{
		if (phi->param.ne != -1 && phi->nb_meal >= phi->param.ne && !i++)
			sem_post(phi->ne_sem);
		if (time_diff(phi->eat, phi->param.ttd))
		{
			process_print(phi, "died");
			sem_post(phi->die);
			return (NULL);
		}
	}
}
