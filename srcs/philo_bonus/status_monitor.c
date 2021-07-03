#include "philo_bonus.h"

void	*status_monitor(void *arg)
{
	int		i;
	t_phi	*phi;

	i = 0;
	phi = (t_phi *)arg;
	while (1)
	{
		if (time_diff(phi->ttd, phi->start))
		{
			process_print(&phi, "died", 3);
			return (clean_exit(phi));
		}
		if ((phi->param.ne != -1 && phi->nb_meal >= phi->param.ne && !i++))
			sem_post(phi->ne_sem);
		usleep(250);
	}
}
