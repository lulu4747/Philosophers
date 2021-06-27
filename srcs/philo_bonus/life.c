#include "philo_bonus.h"

static void sem_ping(t_phi *phi, sem_t *sem)
{
	sem_wait(sem);
	if (phi->closing)
	{
		sem_post(phi->forks);
		sem_post(phi->forks);
		pthread_join(phi->tid_end, NULL);
		pthread_join(phi->tid_status, NULL);
		sem_post(sem);
		clean_exit(phi);
	}
	sem_post(sem);
}

static void	nap(t_phi *phi)
{
	struct timeval	timevl;

	sem_ping(phi, phi->death_print);
	gettimeofday(&timevl, NULL);
	process_print(phi, "is sleeping");
	while (!(time_diff(timevl, phi->param.tts)))
		usleep(1);
}

static void	eat(t_phi **phi)
{
	sem_ping(*phi, (*phi)->death_print);
	gettimeofday(&((*phi)->eat), NULL);
	process_print((*phi), "is eating");
	(*phi)->nb_meal++;
	while (!(time_diff((*phi)->eat, (*phi)->param.tte)))
		usleep(1);
}

static void	life_cycle(t_phi *phi)
{
	sem_ping(phi, phi->death_print);
	sem_wait(phi->forks);
	sem_ping(phi, phi->death_print);
	process_print(phi, "has taken a fork");
	sem_ping(phi, phi->death_print);
	sem_wait(phi->forks);
	sem_ping(phi, phi->death_print);
	process_print(phi, "has taken a fork");
	sem_ping(phi, phi->death_print);
	eat(&phi);
	sem_post(phi->forks);
	sem_post(phi->forks);
	sem_ping(phi, phi->death_print);
	nap(phi);
	sem_ping(phi, phi->death_print);
	process_print(phi, "is thinking");
}

void	life(t_phi *phi)
{
	sem_wait(phi->abs);
	pthread_create(&(phi->tid_end), NULL, &status_end, (void *)phi);
	phi->ntrd++;
	pthread_create(&(phi->tid_status), NULL, &status_monitor, (void *)phi);
	phi->ntrd++;
	sem_post(phi->abs);
	while (1)
		life_cycle(phi);
}
