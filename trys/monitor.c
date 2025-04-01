/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:58:18 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/01 18:02:44 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Print message function
void	print_message(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}

//Check if the philosopher is dead
int		philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if(get_current_time() - philo->last_meal > time_to_die)
	{
		print_message(philo, "died");
		*philo->dead = 1;
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}