#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

typedef enum	e_opcode
{
	THINKING,
	EATING,
	SLEEPING,
	DIED
}	t_opcode;

#define ERROR_MSG "QUE PM"
typedef pthread_mutex_t pmtx;

typedef struct	s_philo
{
	int				id; //identificador
	long			meals_counter;
	bool			full;
	long			last_meal_time;

	pthread_t		thread; //hilo del filo
	pmtx			*left_fork;
	pmtx			*right_fork;
	struct s_table	*table;
	t_opcode		state;
}	t_philo;
typedef struct	s_table
{
	
	long		num_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation;// a philo dies or all arre full

	t_philo		*philos;
	pmtx		*forks;
	pmtx		print_lock;//Evitar que se solapen los msj
}	t_table;

void	error_exit(const char *error);
//Parsing
void	parse_input(t_table *table, char *argv);

//Safe fnct
void	*safe_malloc(size_t size);
void	safe_mutex_init(pmtx *mutex);
void	safe_thread_create(pthread_t *thread, void *(*start_routine)(void *), void arg);
void	safe_thread_join(pthread_t thread);



#endif
