#ifndef PHILO.H
# define PHILO.H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define ERROR_MSG "QUE PM"

typedef struct	s_philosophers
{
	int				id; //identificador
	pthread_t		thread; //hilo del filo
	pmtx			*left_fork;
	pmtx			*right_fork;
	int				times_ate;
	int				max_times_eat;
}	t_philosophers;
typedef struct	s_table
{
	int		num_philo;
	
}
void	error_exit(const char *error);

#endif
