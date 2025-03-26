#include "philo.h"

void	*dinner_simulation(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	wait_all_threads(philo->table);

	while (!philo->table->end_simulation)
	{
		// El filósofo piensa
		printf("Philosopher %d is thinking.\n", philo->id);
		usleep(1000);  // Simulación de pensar, por ejemplo, 1ms

		// El filósofo toma los tenedores
		safe_mutex_lock(&philo->left_fork);
		printf("Philosopher %d is picking up left fork.\n", philo->id);
		safe_mutex_lock(&philo->right_fork);
		printf("Philosopher %d is picking up right forks.\n", philo->id);

		// El filósofo come
		printf("Philosopher %d is eating.\n", philo->id);
		usleep(1000);  // Simulación de comer, por ejemplo, 1ms

		// El filósofo deja los tenedores
		safe_mutex_unlock(&philo->left_fork);
		printf("Philosopher %d is putting down left fork.\n", philo->id);
		safe_mutex_unlock(&philo->right_fork);
		printf("Philosopher %d is putting down right fork.\n", philo->id);

		// El filósofo duerme
		printf("Philosopher %d is sleeping.\n", philo->id);
		usleep(1000);  // Simulación de dormir, por ejemplo, 1ms
	}

	return NULL;
}



//Important
void	dinner_start(t_table *table)
{
	int	i;
	
	i = 0;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->nbr_limit_meals == 1)
		return ;//TODO
	else
	{
		while (i < table->num_philo)
		{
			safe_thread_create(&table->philos[i].thread, dinner_simulation, &table->philos[i]);
			i++;
		}
	}
	//Start simu
	table->start_simulation = gettime(MILISECS);

	//All threads ready
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	
	// Wait 4 everyone
	i = 0;
	while (i < table->num_philo)
	{
		safe_thread_join(&table->philos[i].thread);
		i++;
	}
}