#include "philo.h"

static int	save_parameter(char **av, int **params, int i)
{
	if (ft_is_number(av[i + 1]) == 1)
	{
		free(*params);
		ft_putstr_fd("Error : Non-digit argument\n", 2);
		return (1);
	}
	if (ft_atoi_secure(&((*params)[i]), av[i + 1]) == 1)
	{
		free(*params);
		ft_putstr_fd("Error : Overflow\n", 2);
		return (1);
	}
	if ((*params)[i] <= 0)
	{
		free(*params);
		ft_putstr_fd("Error : Negative value\n", 2);
		return (1);
	}
	if (i == NP && params[i] == 0)
	{
		free(params);
		ft_putstr_fd("Error : number_of_philosophers can't be 0\n", 2);
		return (1);
	}
	return (0);
}

int parsing(int ac, char **av, int **params)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error : Wrong number of arguments\n", 2);
		return (1);
	}
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