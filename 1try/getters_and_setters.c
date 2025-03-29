#include "philo.h"

//Module to avoid writing LOCK UNLOCK everywhere

//BOOL
void	set_bool(pmtx *mutex, bool dest, bool *value)
{
	safe_mutex_lock(mutex);
	*value = dest;
	safe_mutex_unlock(mutex);
}

bool	get_bool(pmtx *mutex, bool *value)
{
	bool	ret;

	safe_mutex_lock(mutex);
	ret = *value;
	safe_mutex_unlock(mutex);
	return (ret);
}

//LONG
long	get_long(pmtx *mutex, long *value)
{
	long	ret;

	safe_mutex_lock(mutex);
	ret = *value;
	safe_mutex_unlock(mutex);
	return (ret);
}

void	set_long(pmtx *mutex, long dest, long *value)
{
	safe_mutex_lock(mutex);
	*value = dest;
	safe_mutex_unlock(mutex);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

 