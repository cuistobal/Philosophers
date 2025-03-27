#include "philosophers.h"

//
static bool	dead_or_full(t_tabl *table, t_phil *philo, int *full)	
{
	if (you_are_dead(philo))
		return (false);
	if (philo->table->params[END] >= 0)
	{
		if (philo->stats[EATEN] == table->params[END])
			full++;
	}
	return (true);
}

//This function checks my boi did not starve not got enough pasta. 
bool	alive_and_not_full(t_tabl *table)
{
	int		full;
	int		index;

	full = 0;
	while (1)
	{
    	index = -1;
		pthread_mutex_lock(&table->monitoring);
    	while (index++ < table->params[CNT])
    	{
			if (dead_or_full(table, &table->philo[index], &full))
				return false;
    	}
		pthread_mutex_unlock(&table->monitoring);
		if (full == table->params[CNT])
			break;
	}
	return (true);
}
