/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:04:06 by dcampas-          #+#    #+#             */
/*   Updated: 2025/04/01 18:02:47 by dcampas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_atoi(char *str)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

//Get the time in milisec
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 1)
		write(2, "Error getting time\n", 20);
	return (time.tv_sec * 1000 + time.tv_sec / 1000);
}

int		ft_usleep(size_t millisec)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < millisec)
		usleep(500);
	return (0);
}