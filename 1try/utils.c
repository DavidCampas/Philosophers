#include "philo.h"

//time_code -> SECONDS MILISECOND MICRSECONDS
long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{	error_exit("GTOD failed");
		return 1;
	}
	if (time_code == SECS)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else if (time_code == MILISECS)
		return (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3);
	else if (time_code == MICROSECS)
		return (tv.tv_sec * 1e6) + (tv.tv_usec);
	else
		error_exit("wrong input to GTOD");
	return (1);
}

void	error_exit(const char *error)
{
	printf("🚨 %s 🚨\n", error);
	exit (1);
}