#include "philo_bonus.h"

static void	nap(t_phi *phi)
{
	struct timeval	timevl;

	gettimeofday(&timevl, NULL);
	process_print(phi, "is sleeping");
	while (!(time_diff(timevl, phi->param.tts)))
		usleep(500);
}

static void	eat(t_phi **phi)
{
	gettimeofday(&((*phi)->eat), NULL);
	process_print((*phi), "is eating");
	(*phi)->nb_meal++;
	while (!(time_diff((*phi)->eat, (*phi)->param.tte)))
		usleep(500);
}

static void	life_cycle(t_phi *phi)
{
	sem_wait(phi->forks);
	process_print(phi, "has taken a fork");
	sem_wait(phi->forks);
	process_print(phi, "has taken a fork");
	eat(&phi);
	sem_post(phi->forks);
	sem_post(phi->forks);
	nap(phi);
	process_print(phi, "is thinking");
}

void	life(t_phi *phi)
{
	phi->forks = sem_open("forks", O_RDWR);
	phi->abs = sem_open("abs", O_RDWR);
	phi->die = sem_open("die", O_RDWR);
	if (phi->param.ne != -1)
		phi->ne_sem = sem_open("ne", O_RDWR);
	pthread_create(&(phi->tid), NULL, &status_monitor, (void *)phi);
	pthread_detach(phi->tid);
	while (1)
		life_cycle(phi);
}
