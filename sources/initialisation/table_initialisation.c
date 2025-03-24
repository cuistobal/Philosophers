#include "philosophers.h"

//I wish you know about this video. Otherwise check it out (Italian guy goes 
//to vacation in Malta).
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

static bool a_wild_philosophers_appears(t_tabl **table, t_phil **philo, int pos, int pcount)
{
    int index;

    index = 0;
    if (*philo)
    {
        while (index < PARAMS)
        {
            (*philo)[pos].params[index] = (*table)->params[index];
            index++;
        }
        (*philo)[pos].stats[POSTN] = pos + 1;
		(*philo)[pos].stats[LMEAL] = 0;
		(*philo)[pos].stats[EATEN] = 0;
        (*philo)[pos].lfork = &(*table)->fork[pos];
        (*philo)[pos].rfork = &(*table)->fork[(pos + 1) % pcount];
        if (pthread_create(&(*philo)[pos].thread, NULL, routine, &(*philo)[pos]) != 0)
            return (cleanup(table, THREAD_CREATE));
        return (true);
    }
    return (false);
}

//A bunch of hungover dudes pops in the tavern to sit around a table where they
//pretend to think while trying to access the neighbours fork to eat pasta.
static bool	the_emergence_of_philosophy(t_tabl **table)
{
	int		pos;
    int     pcount; 
    t_phil  *philos;

	pos = 0;
    philos = NULL;
    pcount = (*table)->params[CNT];
    if (*table)
	{
		philos = malloc(sizeof(t_phil) * pcount);
		if (philos)
		{
		    (*table)->philo = philos;
			while (pos < pcount)
			{
                if (!a_wild_philosophers_appears(table, &philos, pos, pcount))
                    return (false);
                pos++;
			}
            return (true);
		}
	}
    return (false);
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
                return (cleanup(table, ATOI, argv[index]));
			(*table)->params[index] = my_atoi(argv[index]);	
			index++;
		}
		(*table)->fork = NULL;
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
		if (!i_wanna_fork_on_the_table(table))
			return (false);
		return (the_emergence_of_philosophy(table));
	}
	return (*table);
}
