/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:42 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/21 19:37:44 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

pid_t	processes_launcher(int *params)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (pid);
	if (pid == 0)
		
}

int	philosophy(int *params)
{
	sem_t	*sem_state;

	sem_state = sem_open("state", O_CREAT, 0644, 0);
	free(params);
	return (0);
}
