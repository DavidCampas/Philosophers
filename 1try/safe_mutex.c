#include "philo.h"

void	safe_mutex_init(pmtx *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_mutex_lock(pmtx *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("Error: mutex lock failed\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_mutex_unlock(pmtx *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("Error: mutex unlock failed\n");
		exit(EXIT_FAILURE);
	}
}