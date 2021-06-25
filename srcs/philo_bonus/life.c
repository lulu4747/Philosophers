#include "philo_bonus.h"

void	life(t_phi phi)
{
	phi.forks = sem_open("forks", O_RDWR);
	phi.abs = sem_open("abs", O_RDWR);
	phi.die = sem_open("die",O_RDWR);
	printf("%d\n", phi.id);
	sleep(10);
	sem_post(phi.die);
	sleep (1000);
	exit(EXIT_SUCCESS);
}