#include "philo.h"

int main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		//CORRECT
		
		//Check errors
		parse_input(&table, argv);

		data_init(&table);
		
		//No leaks -> philos full | 1 died
		//clean(&table);
	}
	else
	{
		//WRONG
		error_exit("Wrong input: \n");
	}
}