#include "philosophers.h"

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
		philo->stats[LMEAL] = get_timestamp();
		if (pthread_create(&philo->thread, NULL, routine, philo) != 0)
			cleanup(table, THREAD_CREATE);
		index++;
	}
	if (!alive_and_not_full(*table))
		return ;
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
	t_tabl			*table;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		if (init_table(&table, argv))
		{
			dinner_time(&table);
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
}
