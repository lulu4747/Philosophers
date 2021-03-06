/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:36:36 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 18:15:55 by user42           ###   ########.fr       */
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
	int				even;
	int				start;
	int				ttd;
	int				tte;
	int				tts;
	int				closing;
	int				nb_meal;
	int				*params;
	pthread_t		tid;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*eating;
	pthread_mutex_t	*abs;
	struct s_phi	*next;
}	t_phi;

typedef struct s_status
{
	pthread_t		tid;
	int				ts;
	t_frk			*frk;
	t_phi			*phi;
	pthread_mutex_t	*abs;
}	t_status;

int				parsing(int ac, char **av, int **params);
int				philosophy(int *params);
void			*life(void *arg);
void			*death(t_phi *phi);
int				milliseconds(struct timeval time);
int				time_diff(int n, int start);
int				ts_ms(int start);
int				abs_lock(t_phi **phi);
int				fork_lock(t_phi **phi);
t_frk			*frk_builder(int n);
void			frk_free(t_frk *frk);
t_status		*status_builder(int *params, t_status *status);
void			*philosophers_status(void *arg);
t_status		*status_clean(t_status *status);
pthread_mutex_t	*mtx_create(const pthread_mutexattr_t *restrict attr);
pthread_mutex_t	*mtx_destroy(pthread_mutex_t *mtx);

#endif
