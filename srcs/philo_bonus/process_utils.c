#include "philo_bonus.h"

void	*clean_exit(t_phi *phi)
{
	if (phi->forks)
		sem_close(phi->forks);
	sem_close(phi->die);
	sem_close(phi->death_print);
	if (phi->ne_sem)
		sem_close(phi->ne_sem);
	sem_post(phi->abs);
	sem_close(phi->abs);
	if (phi->ntrd >= 1)
		pthread_detach(phi->tid_end);
	if(phi->ntrd == 2)
		pthread_detach(phi->tid_status);
	exit(EXIT_SUCCESS);
}

void	*status_end(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	sem_wait(phi->die);
	sem_wait(phi->abs);
	phi->closing = 1;
	if (!phi->id)
		sem_post(phi->ne_sem);
	return (NULL);
}

void	process_print(t_phi *phi, char *str)
{
	sem_wait(phi->abs);
	printf("%d %d %s\n", ts_ms(phi->start), phi->id, str);
	if (ft_strcmp(str, "died"))
		sem_post(phi->abs);
}
