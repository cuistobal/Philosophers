/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 15:34:39 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static bool	a_wild_philosopher_appears(t_tabl *table, int pos, int pcount)
{
	t_phil	*philo;

	philo = &table->philo[pos];
	philo->table = table;
	philo->stats[POSTN] = pos;
	philo->stats[EATEN] = 0;
	philo->stats[LMEAL] = 0;
	philo->stats[START] = 0;
	return (sem_init(&philo->clock, 1, 0) == 0);
}

//A bunch of hungover dudes pops in the tavern to sit around a table where they
//pretend to think while trying to access the neighbours fork to eat pasta.
static bool	the_emergence_of_philosophy(t_tabl *table)
{
	int		pos;
	pid_t	pid;
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
	table->pids = NULL;
	table->philo = NULL;
	table->params[STS] = -1;
	while (index < TABLES)
	{
		temp = my_atoi(argv[index]);
		if (temp < 0)
			return (false);	
		table->params[index] = temp;
		index++;
	}
//	return (sem_init(table));
}

//
bool	init_table(t_tabl **table, char **argv)
{
	*table = (t_tabl *)malloc(sizeof(t_tabl));
	if (!*table)
		return (false);	
	if (!append_table_parameters(*table, argv))
		return (false);
	return (the_emergence_of_philosophy(*table));
}
