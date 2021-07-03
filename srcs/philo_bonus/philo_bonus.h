/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:35 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 15:22:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>       
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define NP	0
# define TD	1
# define TE	2
# define TS	3
# define NE 4

typedef struct s_param
{
	int	np;
	int	ttd;
	int	tte;
	int	tts;
	int	ne;
}	t_param;

typedef struct s_phi
{
	int			id;
	pthread_t	tid;
	int			nb_meal;
	int			start;
	int			ttd;
	int			tte;
	int			tts;
	t_param		param;
	sem_t		*prio;
	sem_t		*forks;
	sem_t		*abs;
	sem_t		*death_print;
	sem_t		*ne_sem;
}	t_phi;

int		parsing(int ac, char **av, t_param *params);
int		philosophy(t_param param);
int		processes(t_phi phi);
int		milliseconds(struct timeval time);
int		time_diff(int n, int start);
int		ts_ms(int start);
void	life(t_phi *phi);
void	*process_print(t_phi **phi, char *str, int mode);
void	*status_monitor(void *arg);
void	*clean_exit(t_phi *phi);

#endif
