/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:42:51 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/01 18:02:42 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Init the input from the user
static void	init_input(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

//Init the philos
void	init_philos(t_philo *philos, t_program *program, pmtx *forks, char **argv)
{
	int	i;

	i = -1;
	while (++i < philos->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		init_input(&philos[i], argv);

		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();

		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos->num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
	}
}
//Init forks mutexes
void	init_forks(pmtx *forks,int philo_num)
{
	int	i;

	i = -1;
	while(++i < philo_num)
		pthread_mutex_init(&forks[i], NULL);
}

void	init_program(t_program *program, t_philo *philo)
{
	program->dead_flag = 0;
	program->philos = philo;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}