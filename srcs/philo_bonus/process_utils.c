#include "philo_bonus.h"

void	*clean_exit(t_phi *phi)
{
	if (phi->forks)
		sem_close(phi->forks);
	sem_close(phi->death_print);
	if (phi->ne_sem)
		sem_close(phi->ne_sem);
	sem_close(phi->abs);
	if (phi->id != 0)
		pthread_detach(phi->tid);
	exit(EXIT_SUCCESS);
}

void	process_print(t_phi *phi, char *str, struct timeval *tv)
{
	sem_wait(phi->death_print);
	sem_wait(phi->abs);
	if (tv != NULL)
		gettimeofday(tv, NULL);
	printf("%d %d %s\n", ts_ms(phi->start), phi->id, str);
	sem_post(phi->abs);
	if (ft_strcmp(str, "died"))
		sem_post(phi->death_print);
}
