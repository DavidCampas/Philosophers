#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5 // n de filosofos

pthread_mutex_t forks[N];

typedef struct philosopher {
	int id;
	int	meals;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
} philosopher;

void	think(int id)
{
	printf("Philosopher %d is thinking\n", id);
	usleep(1000000);
}

void	eat(philosopher *p)
{
	p->meals++;
	printf("Philosopher %d is eating (Meal %d)\n", p->id, p->meals);
	usleep(1000000);
}

void	*philosopher_routine(void *arg)
{
	philosopher *p = (philosopher *)arg;

	while (1)
	{
		think(p->id);

	//Tomar tenedores de mayor a menor
		if (p->id % 2 == 0)
		{
			pthread_mutex_lock(p->left_fork);
			//printf("Philosopher %d took left fork\n", p->id);
			//usleep(1000);
			pthread_mutex_lock(p->right_fork);
			//printf("Philosopher %d took right fork\n", p->id);
		}
		else
		{
			pthread_mutex_lock(p->right_fork);
			//printf("Philosopher %d took right fork\n", p->id);
			pthread_mutex_lock(p->left_fork);
			//printf("Philosopher %d took left fork\n", p->id);
		}

		eat(p);

	//Liberar tenedores de menor a mayor
		pthread_mutex_unlock(p->left_fork);
		//printf("Philosopher %d put down left fork\n", p->id);
		pthread_mutex_unlock(p->right_fork);
		//printf("Philosopher %d put down right fork\n", p->id);

		if (p->meals >= 5)
			break;
	}
	return (NULL);
}


int main()
{
	pthread_t	philosophers[N];
	philosopher	philo[N];
	
	int i = 0;

	while (i < N)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}

	i = 0;
	while (i < N)
	{
		philo[i].id = i;
		philo[i].meals = 0;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % N];
		pthread_create(&philosophers[i], NULL, philosopher_routine, &philo[i]);
		i++;
	}

	i = 0;
	while (i < N)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}

	i = 0;
	while (i < N)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}

	return (0);
}