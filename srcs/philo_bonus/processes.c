#include "philo_bonus.h"

static int	destroy(t_phi phi, pid_t *tab, int r)
{
	while (--phi.id >= 0)
		kill(tab[phi.id], SIGKILL);
	sem_unlink("prio");
	sem_unlink("forks");
	sem_unlink("abs");
	sem_unlink("death_print");
	sem_unlink("ne");
	sem_close(phi.prio);
	sem_close(phi.forks);
	sem_close(phi.abs);
	sem_close(phi.death_print);
	if (phi.ne_sem)
		sem_close(phi.ne_sem);
	return (r);
}

static int	meals_counter(t_phi phi, int *pid, pid_t *tab)
{
	*pid = fork();
	if (*pid < 0)
		return (destroy(phi, tab, 1));
	if (*pid == 0)
	{
		phi.id = 0;
		while (--phi.param.np >= 0)
			sem_wait(phi.ne_sem);
		sem_wait(phi.death_print);
		clean_exit(&phi);
	}
	return (0);
}

static int	one_phi(t_phi phi, pid_t *tab)
{
	int	wait;

	wait = (phi.ttd * 1000) + 11000;
	usleep(wait);
	kill(tab[0], SIGKILL);
	if (phi.param.ne != -1)
		kill(tab[1], SIGKILL);
	sem_unlink("prio");
	sem_unlink("forks");
	sem_unlink("abs");
	sem_unlink("death_print");
	sem_unlink("ne");
	sem_close(phi.prio);
	sem_close(phi.forks);
	sem_close(phi.abs);
	sem_close(phi.death_print);
	if (phi.ne_sem)
		sem_close(phi.ne_sem);
	return (0);
}

static int	phi_launch(pid_t pid, t_phi phi)
{
	if (pid < 0)
		return (1);
	if (pid == 0)
		life(&phi);
	return (0);
}

int	processes(t_phi phi)
{
	pid_t	pid;
	pid_t	tab[201];

	while (++phi.id <= phi.param.np)
	{
		pid = fork();
		if (phi_launch(pid, phi))
			return (destroy(phi, tab, 1));
		else
			tab[phi.id - 1] = pid;
		if (phi.param.ne != -1 && phi.id == phi.param.np)
		{
			if (meals_counter(phi, &pid, tab))
				return (1);
			tab[phi.id] = pid;
		}
	}
	if (phi.param.np != 1)
		waitpid(0, NULL, 0);
	else
		return (one_phi(phi, tab));
	if (phi.param.ne == -1)
		phi.id--;
	return (destroy(phi, tab, 0));
}
