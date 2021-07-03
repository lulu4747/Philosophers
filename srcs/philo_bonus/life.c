#include "philo_bonus.h"

static void	nap(t_phi *phi)
{
	process_print(&phi, "is sleeping", 2);
	while (!(time_diff(phi->tts, phi->start)))
		usleep(250);
}

static void	eat(t_phi **phi)
{
	process_print(phi, "is eating", 1);
	while (!(time_diff((*phi)->tte, (*phi)->start)))
		usleep(250);
}

static void	life_cycle(t_phi *phi)
{
	sem_wait(phi->prio);
	sem_wait(phi->forks);
	process_print(&phi, "has taken a fork", 0);
	sem_wait(phi->forks);
	process_print(&phi, "has taken a fork", 0);
	sem_post(phi->prio);
	eat(&phi);
	sem_post(phi->forks);
	sem_post(phi->forks);
	nap(phi);
	process_print(&phi, "is thinking", 0);
	usleep(250);
}

void	life(t_phi *phi)
{
	pthread_create(&(phi->tid), NULL, &status_monitor, (void *)phi);
	pthread_detach(phi->tid);
	while (1)
		life_cycle(phi);
}
