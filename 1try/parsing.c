#include "philo.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static char	*check_valid(const char *str)
{
	long	result;

	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
	{
		printf("Error: Only positive values are allowed.\n");
		exit(EXIT_FAILURE);
	}
	else if (*str == '+')
		str++;
	if (!is_digit(*str))
	{
		printf("Error: Input is not a valid digit.\n");
		exit(EXIT_FAILURE);
	}
	while (*str && is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
		{
			printf("Error: Input exceeds maximum integer value.\n");
			exit(EXIT_FAILURE);
		}
		str++;
	}
	return (char *)str;
}

static long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	str = check_valid(str);
	while (is_digit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	parse_input(t_table *table, char *argv)
{
	table->num_philo = ft_atol(argv[1]);
	table->time_to_die(ft_atol(argv[2]) * 1e3); //Convert to milisec
	table->time_to_eat(ft_atol(argv[3]) * 1e3);
	table->time_to_sleep(ft_atol(argv[4]) * 1e3);

	//Timestamps > 60ms
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4 ||
		table->time_to_sleep < 6e4)
		error_exit("Use timestamps major that 60ms");

	if (table->num_philosophers <= 0)
	{
		printf("Error: Number of philosophers must be greater than 0.\n");
		exit(EXIT_FAILURE);
	}
	
}