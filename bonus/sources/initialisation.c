/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 11:17:11 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
static bool	a_wild_philosopher_appears(t_tabl *table, int pos, int pcount)
{
	table->philo[pos - 1].pid = 0;
	table->philo[pos - 1].table = table;
	table->philo[pos - 1].stats[POSTN] = pos;
	table->philo[pos - 1].stats[EATEN] = 0;
	table->philo[pos - 1].stats[LMEAL] = 0;
	table->philo[pos - 1].stats[START] = 0;
	sem_init();
	return ();
}

static bool	sem_init(t_tabl *table)
{
	if (table)
	{
		table->forks = sem_open();
		if ()
	}
	return (false);
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
		/*
		pid = fork();
		if (pid < 0)
			return (false);
		else if (pid > 0)
			table->pid[i] = fork()
		else
			philo[i].pid = table->pid[i];
		*/
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
	table->simulation = true;
	table->params[STS] = -1;
	while (index < TABLES)
	{
		temp = my_atoi(argv[index]);
		if (temp < 0)
			return (false);	
		table->params[index] = temp;
		index++;
	}
	return (sem_init(table));
	/*
	if (table->params[DIE] > (table->params[EAT] + table->params[SLP]))
	{
		table->pids = malloc(sizeof(pid_t) * table->params[CNT]);
		if (table->pids)
			return (sem_init(table));
	}
	*/
//	return (false);
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
