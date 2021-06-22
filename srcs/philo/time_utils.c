/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:24:27 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/22 16:24:29 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	milliseconds(struct timeval time)
{
	int	ret;

	ret = (int)(time.tv_sec * 1000);
	ret += (int)(time.tv_usec / 1000);
	return (ret);
}

int	time_diff(struct timeval diff, int n)
{
	struct timeval	now;
	int				ms_diff;

	gettimeofday(&now, NULL);
	ms_diff = milliseconds(now) - milliseconds(diff);
	if (ms_diff >= n)
		return (1);
	return (0);
}

int	ts_ms(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (milliseconds(now) - milliseconds(start));
}
