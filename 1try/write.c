#include "philo.h"

void	write_status(t_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILISECS) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_lock(&philo->table->write_mutex);
  
	if (!simulation_finished(philo->table))
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%-6ld %d has taken the 1 fork\n", elapsed, philo->id);
		else if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%-6ld %d has taken the 2 fork\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%-6ld %d is eating %ld\n", elapsed, philo->id, philo->meals_counter);
		else if (status == SLEEPING)
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-6ld %d died\n", elapsed, philo->id);
	}

	safe_mutex_unlock(&philo->table->write_mutex);
}
