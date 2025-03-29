#include "philo.h"

static void thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

static void	eat(t_philo *philo)
{
	safe_mutex_lock(philo->table->forks[philo->first_fork]);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_lock(philo->table->forks[philo->second_fork]);
	write_status(TAKE_SECOND_FORK, philo);

	write_status(EATING, philo);
	set_long(&philo->table->table_mutex, philo->last_meal_time, gettime(MILISECS));
	precise_usleep(philo->table->time_to_eat, philo->table);
	philo->meals_counter++;

	safe_mutex_unlock(philo->first_fork);
	safe_mutex_unlock(philo->second_fork);

	if (philo->meals_counter >= philo->table->nbr_limit_meals
		&& philo->table->nbr_limit_meals > 0)
		set_bool(&philo->table->table_mutex, philo->full, true);

	safe_mutex_unlock(&philo->first_fork);
	safe_mutex_unlock(&philo->second_fork);
}

void	*dinner_simulation(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	wait_all_threads(philo->table);

	while (!philo->table->end_simulation)
	{
		if (philo->full)
			break;
		eat(philo);

		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table)
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