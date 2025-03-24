#include "philosophers.h"

//
static bool	i_wanna_fork_on_the_table(t_tabl **table)
{
	int			    index;
	pthread_mutex_t *forks;

	index = 0;
	if (*table)
	{
		forks = malloc(sizeof(pthread_mutex_t) * (*table)->params[CNT]);
		if (forks)
		{
			(*table)->fork = forks;
			while (index < (*table)->params[CNT])
			{
                if (pthread_mutex_init(&forks[index], NULL) != 0)
					return (false);
				index++;
			}
		}
		return ((*table)->fork);
	}
	return (*table);
}

//A bunch of hungover dudes pops in the tavern to sit around a table where they
//pretend to think while trying to access the neighbours fork to eat pasta.
static bool	the_emergence_of_philosophy(t_tabl **table)
{
	int		pos;
    t_phil  *philos;

	pos = 0;
    philos = NULL;	
    if (*table)
	{
		philos = malloc(sizeof(t_phil) * (*table)->params[CNT]);
		if (philos)
		{
		    (*table)->philo = philos;
			while (pos < (*table)->params[CNT])
			{
				philos[pos].stats[POSTN] = pos + 1 ;
				philos[pos].stats[LMEAL] = 0;
				philos[pos].stats[EATEN] = 0;
				if (pthread_create(&philos[pos].thread, NULL, routine, NULL) != 0)
                    return (false);
				pos++;
			}
		}
		return ((*table)->philo);
	}
	return (*table);
}

//How would you sit and share a meal if it wasn't for a table to be dressed up!
//This function initialises the table's parameter.
static bool	append_table_parameters(t_tabl **table, char **argv)
{
	int	temp;
	int	index;

	temp = 0;
	index = 0;
	if (*table)
	{
		while (index < PARAMS)
		{
			temp = my_atoi(argv[index]);
			if (temp < 0)
				return (free(*table), *table = NULL, false);		
			(*table)->params[index] = my_atoi(argv[index]);	
			index++;
		}
		(*table)->philo = NULL;
	}
	return (*table);
}

//
bool	init_table(t_tabl **table, char **argv)
{
	*table = (t_tabl *)malloc(sizeof(t_tabl));
	if (*table)
	{
		if (!append_table_parameters(table, argv))
			return (false);
		if (!the_emergence_of_philosophy(table))
			return (false);
		return (i_wanna_fork_on_the_table(table));
	}
	return (*table);
}
