/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_secure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 12:45:19 by lfourage          #+#    #+#             */
/*   Updated: 2021/05/31 12:45:21 by lfourage         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_secure(int *r, char *n)
{
	*r = ft_atoi(n);
	if (*r != ft_atol(n))
		return (1);
	return (0);
}
