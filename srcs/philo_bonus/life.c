#include "philo_bonus.h"

void	life(t_phi phi)
{
	phi.forks = sem_open("forks", O_RDWR);
	phi.abs = sem_open("abs", O_RDWR);
	phi.die = sem_open("die",O_RDWR);
	sem_wait(phi.abs);
	printf("%d\n", phi.id);
	sem_post(phi.abs);
	sleep(5);
	sem_wait(phi.abs);
	sem_post(phi.die);
	sem_unlink("forks");
	sem_unlink("abs");
	sem_unlink("die");
	sleep (1000);
	exit(EXIT_SUCCESS);
}