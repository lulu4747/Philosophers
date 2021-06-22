/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:36:36 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/21 19:36:38 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_frk
{
	pthread_mutex_t	*mtx;
	struct s_frk	*next;
}	t_frk;

typedef struct s_phi
{
	int				id;
	struct timeval	start;
	struct timeval	eat;
	int				nb_meal;
	int				*params;
	pthread_t		tid;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*abs;
	struct s_phi	*next;
	struct s_phi	*prev;
}	t_phi;

typedef struct s_status
{
	pthread_t		tid;
	int				closing;
	t_frk			*frk;
	t_phi			*phi;
	pthread_mutex_t	*abs;
	pthread_mutex_t	*state;
}	t_status;

int				parsing(int ac, char **av, int **params);
int				philosophy(int *params);
void			*life(void *arg);
void			*death(t_phi *phi);
int				milliseconds(struct timeval time);
int				time_diff(struct timeval diff, int n);
int				ts_ms(struct timeval start);
int				abs_lock(t_phi **phi);
int				print_fork(t_phi **phi, int type);
int				fork_lock(t_phi **phi);
t_frk			*frk_builder(int n);
void			frk_free(t_frk *frk);
void			*philosophers_status(void *arg);
t_status		*status_clean(t_status *status);
void			*delone(t_phi **phi);
pthread_mutex_t	*mtx_create(const pthread_mutexattr_t *restrict attr);
pthread_mutex_t	*mtx_destroy(pthread_mutex_t *mtx);

#endif
