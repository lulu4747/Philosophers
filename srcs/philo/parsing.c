/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:36:26 by lfourage          #+#    #+#             */
/*   Updated: 2021/06/21 19:36:28 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	err_print(int **params, int err_code)
{
	if (err_code == 0)
	{
		ft_putstr_fd("Error : Wrong number of arguments\n", 2);
		return (1);
	}
	free(*params);
	if (err_code == 1)
		ft_putstr_fd("Error : Non-digit argument\n", 2);
	if (err_code == 2)
		ft_putstr_fd("Error : Overflow\n", 2);
	if (err_code == 3)
		ft_putstr_fd("Error : Negative or null value\n", 2);
	if (err_code == 4)
		ft_putstr_fd("Error : number_of_philosophers must be > 1\n", 2);
	return (1);
}

static int	save_parameter(char **av, int **params, int i)
{
	if (ft_is_number(av[i + 1]) == 1)
		return (err_print(params, 1));
	if (ft_atoi_secure(&((*params)[i]), av[i + 1]) == 1)
		return (err_print(params, 2));
	if ((*params)[i] <= 0)
		return (err_print(params, 3));
	if (i == NP && (*params)[i] <= 1)
		return (err_print(params, 4));
	return (0);
}

int	parsing(int ac, char **av, int **params)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (err_print(NULL, 0));
	*params = malloc(sizeof(int) * 5);
	if (!(*params))
		return (1);
	i = 0;
	while (i < ac - 1)
	{
		if (save_parameter(av, params, i) == 1)
			return (1);
		i++;
	}
	if (ac == 5)
		(*params)[NE] = -1;
	return (0);
}
