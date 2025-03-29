/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/29 12:07:23 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//I wish you know about this video. Otherwise check it out (Italian guy goes 
//to vacation in Malta).
static bool	i_wanna_fork_on_the_table(t_tabl *table)
{
	int				index;
	pthread_mutex_t	*forks;

	index = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->params[CNT]);
	if (forks)
	{
		table->fork = forks;
		while (index < table->params[CNT])
		{
			if (pthread_mutex_init(&forks[index], NULL) != 0)
				return (false);
			index++;
		}
	}
	return (forks);
}

//
static void	a_wild_philosopher_appears(t_tabl *table, int pos, int pcount)
{
	table->philo[pos].table = table;
	table->philo[pos].stats[POSTN] = pos + 1;
	table->philo[pos].stats[EATEN] = 0;
	table->philo[pos].stats[LMEAL] = 0;
	table->philo[pos].lfork = &table->fork[pos];
	table->philo[pos].rfork = &table->fork[(pos + 1) % pcount];
}

//A bunch of hungover dudes pops in the tavern to sit around a table where they
//pretend to think while trying to access the neighbours fork to eat pasta.
static bool	the_emergence_of_philosophy(t_tabl *table)
{
	int		pos;
	int		pcount;
	t_phil	*philos;

	pos = 0;
	philos = NULL;
	pcount = table->params[CNT];
	philos = malloc(sizeof(t_phil) * pcount);
	if (philos)
	{
		table->params[STS] = get_timestamp();
		table->philo = philos;
		while (pos < pcount)
		{
			a_wild_philosopher_appears(table, pos, pcount);
			pos++;
		}
	}
	return (philos);
}

//How would you sit and share a meal if it wasn't for a table to be dressed up!
//This function initialises the table's parameter.
static bool	append_table_parameters(t_tabl *table, char **argv)
{
	int	temp;
	int	index;

	temp = 0;
	index = 1;
	while (index < TABLES)
	{
		temp = my_atoi(argv[index]);
		if (temp < 0)
			return (cleanup(table, ATOI, argv[index]));
		table->params[index] = my_atoi(argv[index]);
		index++;
	}
	table->fork = NULL;
	table->philo = NULL;
	if (pthread_mutex_init(&table->monitoring, NULL) != 0)
		return (false);
	return (true);
}

//
bool	init_table(t_tabl **table, char **argv)
{
	*table = (t_tabl *)malloc(sizeof(t_tabl));
	if (*table)
	{
		if (!append_table_parameters(*table, argv))
			return (false);
		if (!i_wanna_fork_on_the_table(*table))
			return (false);
		return (the_emergence_of_philosophy(*table));
	}
	return (*table);
}
