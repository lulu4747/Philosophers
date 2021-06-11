#include "philo_bonus.h"

int	philosophy(int *params)
{
	printf("%d\n%d\n%d\n%d\n%d\n", params[0], params[1], params[2], params[3], params[4]);
	free(params);
	return (0);
}