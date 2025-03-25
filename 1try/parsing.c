#include "philo.h"

 static char	*check_valid(char *str, long *result, int *sign)
{
	long	max_int = 2147483647;
	long	min_int = -2147483648;

	*result = 0;
	*sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
	{
		perror("Only positive values");
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		*result = *result * 10 + (*str - '0');
		if ((*sign == 1 && *result > max_int) || (*sign == -1 && -*result < min_int))
		{
			printf("Error: Integer value out of range.\n");
			exit(EXIT_FAILURE);
		}
		str++;
	}
	return str;
}

static long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	str = check_valid(str);

	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

void	parse_input(t_table *table, char *argv)
{
	table->num_philo = atoi(argv);
	if (table->num_philosophers <= 0)
	{
		printf("Error: Number of philosophers must be greater than 0.\n");
		exit(EXIT_FAILURE);
	}
	
}