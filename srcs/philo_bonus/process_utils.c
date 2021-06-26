#include "philo_bonus.h"

void	process_print(t_phi *phi, char *str)
{
	sem_wait(phi->abs);
	printf("%d %d %s\n", ts_ms(phi->start), phi->id, str);
	if (ft_strcmp(str, "died"))
		sem_post(phi->abs);
}
