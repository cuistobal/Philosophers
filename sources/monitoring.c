#include "philosophers.h"

bool	i_m_full_daddy(t_phil *philosopher)
{
	if (philosopher->table->params[END] >= 0)
	{
		if (philosopher->stats[EATEN] != philosopher->table->params[END])
			return (false);
	}
	return (true);
}

//This function checks my boi did not starve not got enough pasta. 
bool	alive_and_not_full(t_tabl *table)
{
	int		index;
	int		full_clip;

	full_clip = 0;
	while (1)
	{
    	index = 0;
		pthread_mutex_lock(&table->monitoring);
    	while (index < table->params[CNT])
    	{
			if (you_are_dead(&table->philo[index]))
				return (false);
			if (i_m_full_daddy(&table->philo[index]))
				full_clip++;
			index++;
    	}
		pthread_mutex_unlock(&table->monitoring);
		if (full_clip >= table->params[CNT])
			break;
	}
	return (true);
}
