#include "philo_bonus.h"

void	*clean_exit(t_phi *phi)
{
	sem_wait(phi->abs);
	sem_close(phi->abs);
	phi->param.np *= 2;
	while (--phi->param.np >= 0)
		sem_post(phi->death_print);
	sem_close(phi->death_print);
	sem_close(phi->prio);
	if (phi->forks)
		sem_close(phi->forks);
	if (phi->ne_sem)
		sem_close(phi->ne_sem);
	exit(EXIT_SUCCESS);
}

void	*process_print(t_phi **phi, char *str, int mode)
{
	int	tmp;

	sem_wait((*phi)->death_print);
	while (sem_wait((*phi)->abs) == -1)
		usleep(10);
	tmp = ts_ms((*phi)->start);
	if (mode == 1)
	{
		(*phi)->ttd = tmp + (*phi)->param.ttd;
		(*phi)->tte = tmp + (*phi)->param.tte;
		(*phi)->nb_meal++;
	}
	if (mode == 2)
		(*phi)->tts = tmp + (*phi)->param.tts;
	printf("%d %d %s\n", tmp, (*phi)->id, str);
	sem_post((*phi)->abs);
	if (mode != 3)
		sem_post((*phi)->death_print);
	return (NULL);
}
