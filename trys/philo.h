#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define PHILO_MAX 300
typedef pthread_mutex_t	pmtx;

typedef struct	s_philo
{
	pthread_t	thread;
	int			id;
	int			eating;
	int			meals_eaten;
	size_t		last_meal;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		start_time;
	int			num_of_philos;
	int			num_times_to_eat;
	int			*dead;
	pmtx		*r_fork;
	pmtx		*l_fork;
	pmtx		*write_lock;
	pmtx		*dead_lock;
	pmtx		*meal_lock;
}				t_philo;

typedef struct s_program
{
	int			dead_flag;
	pmtx		dead_lock;
	pmtx		meal_lock;
	pmtx		write_lock;
	t_philo		*philos;
}				t_program;

//Utils
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
size_t	get_current_time(void);
int		ft_usleep(size_t millisec);

//Threads
void	*philo_routine(void *pointer);
int		thread_create(t_program *program, pmtx *forks);
void	*monitor(void *pointer);
void	destroy_all(char *str, t_program *program, pmtx *forks);

//
void	init_program(t_program *program, t_philo *philo);
void	init_philos(t_philo *philos, t_program *program, pmtx *forks, char **argv);
void	init_forks(pmtx *forks, int philo_num);


#endif