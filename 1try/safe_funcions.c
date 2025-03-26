#include "philo.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	safe_mutex_init(pmtx *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg)
{
	if (pthread_create(thread, NULL, start_routine, arg) != 0)
	{
		printf("Error: thread creation failed\n");
		exit(EXIT_FAILURE);
	}
}

void	safe_thread_join(pthread_t thread)
{
	if (pthread_join(thread, NULL) != 0)
	{
		printf("Error: thread join failed\n");
		exit(EXIT_FAILURE);
	}
}