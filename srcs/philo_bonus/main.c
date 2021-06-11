#include "philo_bonus.h"

int	main(int ac, char **av)
{
	int *params;

	if (parsing(ac, av, &params) == 1)
		return (1);
	return (philosophy(params));
}