/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:35:59 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 17:10:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int	*params;

	if (parsing(ac, av, &params) == 1)
		return (1);
	if (!params[NP] || !params[NE])
	{
		free(params);
		return (0);
	}
	return (philosophy(params));
}
