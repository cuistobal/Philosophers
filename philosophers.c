#include "philosophers.h"

static bool alive_and_not_full(t_tabl *table)
{
	int		index;

	while (1)
	{
    	index = 0;
		pthread_mutex_lock(&table->monitoring);
    	while (index < table->params[CNT])
    	{
			//if (you_are_dead(table->philo[index])) 
			//	return false;
			index++;
    	}
		pthread_mutex_unlock(&table->monitoring);
	}
	return (true);
}

//
int	main(int argc, char **argv)
{
	t_tabl			*table;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		if (init_table(&table, argv))
		{
            while (1)
			{
				if (!alive_and_not_full(table))
					break ;
			}
			//
			//join
	        cleanup(&table, NULL);
            return 0;
        }
		return (cleanup(&table, INIT_TABLE));
	}
	return (cleanup(&table, ARGC));
}
