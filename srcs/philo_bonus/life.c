#include "philo_bonus.h"

static void	nap(t_phi *phi)
{
	struct timeval	tv;

	process_print(phi, "is sleeping", &tv);
	while (!(time_diff(tv, phi->param.tts)))
		usleep(10);
}

static void	eat(t_phi **phi)
{
	process_print((*phi), "is eating", &((*phi)->eat));
	(*phi)->nb_meal++;
	while (!(time_diff((*phi)->eat, (*phi)->param.tte)))
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
	while (1)
		life_cycle(phi);
}
