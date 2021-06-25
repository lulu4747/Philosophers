/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:24:27 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/25 23:51:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
