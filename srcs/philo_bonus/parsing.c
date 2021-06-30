/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:28 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/25 23:28:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	err_print(int err_code)
{
	if (err_code == 0)
		ft_putstr_fd("Error: number of arguments\n", 2);
	if (err_code == 1)
		ft_putstr_fd("Error: Non-digit argument\n", 2);
	if (err_code == 2)
		ft_putstr_fd("Error: Overflow\n", 2);
	if (err_code == 3)
		ft_putstr_fd("Error: Negative argument\n", 2);
	if (err_code == 4)
		ft_putstr_fd("Error: number_of_philosophers > 200\n", 2);
	return (1);
}

static int	*wich(int i, t_param *param)
{
	if (i == NP)
		return (&(param->np));
	if (i == TD)
		return (&(param->ttd));
	if (i == TE)
		return (&(param->tte));
	if (i == TS)
		return (&(param->tts));
	return (&(param->ne));
}

static int	save_parameter(char **av, t_param *param, int i)
{
	int	*ptr;

	ptr = wich(i, param);
	if (ft_is_number(av[i + 1]) == 1)
		return (err_print(1));
	if (ft_atoi_secure(ptr, av[i + 1]) == 1)
		return (err_print(2));
	if (*ptr < 0)
		return (err_print(3));
	if (i == NP && *ptr > 200)
		return (err_print(4));
	return (0);
}

int	parsing(int ac, char **av, t_param *param)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (err_print(0));
	i = 0;
	while (i < ac - 1)
	{
		if (save_parameter(av, param, i) == 1)
			return (1);
		i++;
	}
	if (ac == 5)
		param->ne = -1;
	return (0);
}
