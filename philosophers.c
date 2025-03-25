#include "philosophers.h"

static bool alive_and_not_full(t_tabl *table)
{
    u_int64_t	index;

    index = 0;
    while (index < table->params[CNT])
    {
		if (pthread_join(table->philo[index].thread, NULL) != 0) 
	//		return (error_message());	 
			return false;
		index++;
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
		if (init_table(&table, argv + 1))
		{
            while (1)
			{
				if (!alive_and_not_full(table))
					break ;
			}
	        cleanup(&table, NULL);
            return 0;
        }
		return (cleanup(&table, INIT_TABLE));
	}
	return (cleanup(&table, ARGC));
//	return (printf("%s\n", ARGC));
}
