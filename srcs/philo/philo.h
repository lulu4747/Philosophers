#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

# define NP	0
# define TD	1
# define TE	2
# define TS	3
# define NE 4

typedef struct s_phi
{
	int				id;
	struct timeval	eat;
	struct timeval	sleep;
	struct timeval	tmp;
	int				state;
	int				health;
	int				*params;
	pthread_t		tid;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
	pthread_mutex_t	abs;
	struct s_phi	*next;
}	t_phi;

int		parsing(int ac, char **av, int **params);
int		philosophy(int *params);
void	*life(void *arg);
t_phi	*death(t_phi *phi);

#endif
