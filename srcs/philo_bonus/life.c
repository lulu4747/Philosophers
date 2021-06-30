#include "philo_bonus.h"

static void	nap(t_phi *phi)
{
	struct timeval	tv;

	process_print(phi, "is sleeping", &tv);
	phi->tts = ts_ms(phi->start) + phi->param.tts;
	while (!(time_diff(phi->tts, phi->start)))
		usleep(10);
}

static void	eat(t_phi **phi)
{
	int	tmp;

	process_print((*phi), "is eating", &((*phi)->eat));
	(*phi)->nb_meal++;
	tmp = ts_ms((*phi)->start);
	(*phi)->ttd = tmp + (*phi)->param.ttd;
	(*phi)->tte = tmp + (*phi)->param.tte;
	while (!(time_diff((*phi)->tte, (*phi)->start)))
		usleep(10);
}

static void	life_cycle(t_phi *phi)
{
	sem_wait(phi->prio);
	sem_wait(phi->forks);
	process_print(phi, "has taken a fork", NULL);
	sem_wait(phi->forks);
	process_print(phi, "has taken a fork", NULL);
	sem_post(phi->prio);
	eat(&phi);
	sem_post(phi->forks);
	sem_post(phi->forks);
	nap(phi);
	process_print(phi, "is thinking", NULL);
}

void	life(t_phi *phi)
{
	pthread_create(&(phi->tid), NULL, &status_monitor, (void *)phi);
	pthread_detach(phi->tid);
	while (1)
		life_cycle(phi);
}
