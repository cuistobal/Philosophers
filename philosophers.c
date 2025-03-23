#include "philosophers.h"

//
int	main(int argc, char **argv)
{
	pthread_mutex_t	mutex;
	t_tabl			*table;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		if (pthread_mutex_init(&mutex, NULL) != 0)
			return -1;
		if (init_table(&table, argv + 1))
		{
			lets_get_this_party_started(table);
			the_show_must_go_on(table);
			/*
			t_phil	*prev = NULL;
			
			for (int i = 0; i < PARAMS; i++)
				printf("%d\n", table->params[i]);
			printf("\n");
			for (int i = 0; i < table->params[CNT]; i++)
			{
				if (table->philo)
				{
					printf("%d\n", table->philo->stats[POSTN]);
					prev = table->philo;
					table->philo = table->philo->next;
					free(prev);
					prev = NULL;
				}
			}
			if (prev)
			{
				free(prev);
				prev = NULL;
			}
			free(table);
			*/
						
		}
		pthread_mutex_destroy(&mutex);
		return 0;
	}
	return (printf("%s\n", ARGC));
}
