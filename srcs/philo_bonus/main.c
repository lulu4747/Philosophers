/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:37:22 by lfourage          #+#    #+#             */
/*   Updated: 2021/07/03 17:10:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_param	param;

	if (parsing(ac, av, &param) == 1)
		return (1);
	if (!param.np || !param.ne)
		return (0);
	return (philosophy(param));
}
