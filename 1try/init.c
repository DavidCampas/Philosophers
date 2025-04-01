#include "philo.h"

//Los filósofos pares toman primero el tenedor derecho y los impares el izquierdo,
// el último comparte con el primero usando % num_philo.
static void	assign_forks(t_philo *philo, pmtx *forks, int num_philo)
{
	int	i;

	i = philo->id - 1;

	if (philo->id % 2 == 0)
	{
		philo->second_fork = &forks[i];

		philo->first_fork = &forks[(i + 1) % num_philo];
	}
	else
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % num_philo];
	}

}

static void	philo_init(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = 0;
	while (i < table->num_philo)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_init(&philo->philo_mutex);

		assign_forks(philo, table->forks, table->num_philo);
		i++;
	}
}

void		data_init(t_table *table)
{
	int	i;

	table->end_simulation = false;
	table->all_threads_ready = false;
	table->start_simulation = gettime(MILISECS);
	table->philos = safe_malloc(sizeof(t_philo) * table->num_philo);
	safe_mutex_init(&table->table_mutex);
	table->forks = safe_malloc(sizeof(pmtx) * table->num_philo);

	i = 0;
	while (i < table->num_philo)
	{
		safe_mutex_init(&table->forks[i]);
		i++;
	}
	philo_init(table);
	
}