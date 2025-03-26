#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

typedef enum	e_time_code
{
	SECS,
	MILISECS,
	MICROSECS
}	t_time_code;

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
	bool		end_simulation;// a philo dies or all are full
	
	bool		all_threads_ready;//bandera que indica si los hilos estan listos
	int			threads_count;//Contador de hilos
	pmtx		table_mutex;//avoid races while reading from table
	t_philo		*philos;
	pmtx		*forks;
	pmtx		print_lock;//Evitar que se solapen los msj
}	t_table;

//Utils
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
//Parsing
void	parse_input(t_table *table, char *argv);

//Synchro utils
void	wait_all_threads(t_table *table);

//Safe fnct
void	*safe_malloc(size_t size);
void	safe_thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg);
void	safe_thread_join(pthread_t thread);

void	safe_mutex_init(pmtx *mutex);
void	safe_mutex_lock(pmtx *mutex);
void	safe_mutex_unlock(pmtx *mutex);

//Setters & Getters, readable code
bool	set_bool(pmtx *mutex, bool dest, bool *value);
bool	get_bool(pmtx *mutex, bool *value);
long	get_long(pmtx *mutex, bool *value);
long	set_long(pmtx *mutex, bool dest, bool *value);
bool	simulation_finished(t_table *table);


#endif
