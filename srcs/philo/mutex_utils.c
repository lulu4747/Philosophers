#include "philo.h"

pthread_mutex_t	*mtx_destroy(pthread_mutex_t *mtx)
{
	pthread_mutex_destroy(mtx);
	free(mtx);
	return (NULL);
}

pthread_mutex_t	*mtx_create(const pthread_mutexattr_t *restrict attr)
{
	pthread_mutex_t	*mtx;

	mtx = malloc(sizeof(pthread_mutex_t));
	if (!mtx)
		return (NULL);
	if (pthread_mutex_init(mtx, attr) != 0)
	{
		free(mtx);
		return (NULL);
	}
	return (mtx);
}