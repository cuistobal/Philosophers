/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 14:31:55 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//I wish you know about this video. Otherwise check it out (Italian guy goes 
//to vacation in Malta).
static bool	i_wanna_fork_on_the_table(t_tabl *table)
{
	int	index;

	index = 0;
	table->fork = malloc(sizeof(pthread_mutex_t) * table->params[CNT]);
	if (!table->fork)
		return (false);
	while (index < table->params[CNT])
	{
		if (pthread_mutex_init(&table->fork[index], NULL) != 0)
			return (false);
		index++;
	}
	return (true);
}

//
static bool a_wild_philosopher_appears(t_tabl *table, int pos, int pcount)
{
	table->philo[pos - 1].table = table;
	table->philo[pos - 1].stats[POSTN] = pos;
	table->philo[pos - 1].stats[EATEN] = 0;
	table->philo[pos - 1].stats[LMEAL] = 0;
	table->philo[pos - 1].stats[START] = 0;
	table->philo[pos - 1].lfork = &table->fork[(pos + pcount - 1) % pcount];
	table->philo[pos - 1].rfork = &table->fork[pos % pcount];
	if (pthread_mutex_init(&table->philo[pos - 1].clock, NULL) != 0)
		return (false);
	return (pthread_mutex_init(&table->philo[pos - 1].clock, NULL) == 0); 
}

//A bunch of hungover dudes pops in the tavern to sit around a table where they
//pretend to think while trying to access the neighbours fork to eat pasta.
static bool	the_emergence_of_philosophy(t_tabl *table)
{
	int		pos;
	int		pcount;
	t_phil	*philos;

	pos = 1;
	philos = NULL;
	pcount = table->params[CNT];
	philos = malloc(sizeof(t_phil) * pcount);
	if (!philos)
		return (false);
	table->philo = philos;
	while (pos < pcount + 1)
	{
		if (!a_wild_philosopher_appears(table, pos, pcount))
			return (false);
		pos++;
	}
	return (true);
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
	table->params[STS] = -1;
	table->fork = NULL;
	table->philo = NULL;
	table->simulation = true;
	return (pthread_mutex_init(&table->monitoring, NULL) == 0);
}

//
bool	init_table(t_tabl **table, char **argv)
{
	*table = (t_tabl *)malloc(sizeof(t_tabl));
	if (!*table)
		return (false);
	if (!append_table_parameters(*table, argv))
		return (false);
	if (!i_wanna_fork_on_the_table(*table))
		return (false);
	return (the_emergence_of_philosophy(*table));
}
