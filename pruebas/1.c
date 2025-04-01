#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef pthread_mutex_t pmtx;

typedef struct	s_philosophers
{
	int				id; //identificador
	pthread_t		thread; //hilo del filo
	pmtx			*first_fork;
	pmtx			*second_fork;
	int				times_ate;
	int				max_times_eat;
}	t_philosophers;

#define NUM_PHILO 5

void	think(int id)
{
	printf("Filosofo %d esta pensando... \n", id);
	usleep(1000000); // Simula el tiempo pensando
}

void	eat(int id, t_philosophers *philosopher)
{
	// Si el filósofo es par, bloquea el tenedor izquierdo primero
	// Si es impar, bloquea el tenedor derecho primero
	if (id % 2 == 0)
	{
		pthread_mutex_lock(philosopher->first_fork);
		printf("Filosofo %d ha cogido el tenedor izquierdo\n", id);

		pthread_mutex_lock(philosopher->second_fork);
		printf("Filosofo %d ha cogido el tenedor derecho\n", id);
	}
	else
	{
		pthread_mutex_lock(philosopher->second_fork);
		printf("Filosofo %d ha cogido el tenedor derecho\n", id);

		pthread_mutex_lock(philosopher->first_fork);
		printf("Filosofo %d ha cogido el tenedor izquierdo\n", id);
	}

	printf("Filosofo %d esta comiendo...\n", id);
	usleep(1000000); // Simula el tiempo comiendo

	pthread_mutex_unlock(philosopher->second_fork);
	printf("Filosofo %d ha dejado el tenedor derecho\n", id);
	pthread_mutex_unlock(philosopher->first_fork);
	printf("Filosofo %d ha dejado el tenedor izquierdo\n", id);
}

void	rest(int id)
{
	printf("Filosofo %d esta descansando...\n", id);
	usleep(1000000); // Simula el tiempo descansando
}

void	*philosophers_routine(void *arg)
{
	t_philosophers	*philosopher = (t_philosophers *)arg;
	printf("Filósofo %d ha iniciado su rutina\n", philosopher->id);
	while (philosopher->times_ate < philosopher->max_times_eat)
	{
		think(philosopher->id);
		eat(philosopher->id, philosopher);
		rest(philosopher->id);
		philosopher->times_ate++;
		
	}
	printf("Filosofo %d ha terminado TODO.\n", philosopher->id);
	return NULL;
}

int main()
{
	pmtx			forks[NUM_PHILO];
	t_philosophers	philosophers[NUM_PHILO];
	
	int i = 0;
	// Inicializamos los mutexes para los tenedores
	while (i < NUM_PHILO)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	
	i = 0;
	// Inicializamos los filósofos
	while(i < NUM_PHILO)
	{
		philosophers[i].id = i;
		philosophers[i].first_fork = &forks[i];
		philosophers[i].second_fork = &forks[(i + 1) % NUM_PHILO];
		philosophers[i].times_ate = 0;
		philosophers[i].max_times_eat = 3;
		i++;
	}

	i = 0;
	// Crear los hilos
	while (i < NUM_PHILO)
	{
		pthread_create(&philosophers[i].thread, NULL, philosophers_routine, (void *)&philosophers[i]);
		i++;
	}

	i = 0;
	// Esperar a que todos los hilos terminen
	while (i < NUM_PHILO)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}

	i = 0;
	// Destrucción de mutex
	while (i < NUM_PHILO)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}

	return 0;
}
