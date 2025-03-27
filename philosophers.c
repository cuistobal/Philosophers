#include "philosophers.h"

//
//	STEP 1	->	Set all threads and make them start at the same time
//
//	STEP 2	->	Make sure no one dies
//
//	STEP 3	->	Join all threads
//
static void	dinner_time(t_tabl	**table)
{
	int		index;
	t_phil	*philo;

	index = 0;
	philo = NULL;

	(*table)->params[STS] = get_timestamp();
	
	while (index < (*table)->params[CNT])
	{
		philo = &(*table)->philo[index];
		set_value(&(*table)->monitoring, (void *)&philo->stats[LMEAL], (void *)get_timestamp());
		if (pthread_create(&philo->thread, NULL, routine, &philo[index]) != 0)
			cleanup(table, THREAD_CREATE);
		index++;
	}
	
	alive_and_not_full(*table);
	index = 0;
	
	while (index < (*table)->params[CNT])
	{
		if (pthread_join(philo[index].thread, NULL) != 0)	
			cleanup(table, THREAD_CREATE);
		index++;
	}
}

//
int	main(int argc, char **argv)
{
	t_tabl	*table;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		if (init_table(&table, argv))
		{
			dinner_time(&table);
	        cleanup(&table, NULL);
            return 0;
        }
		return (cleanup(&table, INIT_TABLE));
	}
	return (cleanup(&table, ARGC));
}
