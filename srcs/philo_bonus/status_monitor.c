#include "philo_bonus.h"

void	*status_monitor(void *arg)
{
	int		i;
	t_phi	*phi;

	i = 0;
	phi = (t_phi *)arg;
	while (1)
	{
		if ((phi->param.ne != -1 && phi->nb_meal >= phi->param.ne && !i++) || phi->closing)
		{
			sem_wait(phi->abs);
			sem_post(phi->die);
			return (NULL);
		}
		if (time_diff(phi->eat, phi->param.ttd))
		{
			sem_wait(phi->death_print);
			process_print(phi, "died");
			sem_post(phi->die);
			return (NULL);
		}
	}
	return (clean_exit(phi));
}
