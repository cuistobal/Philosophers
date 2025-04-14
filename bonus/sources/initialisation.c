/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 12:57:33 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static bool	a_wild_philosopher_appears(t_tabl *table, int pos)
{
	char	*semaname;

	semaname = table->philo[pos -1].semaname;
	memset(semaname, 0, BUFFER_SIZE * sizeof(char));
	table->philo[pos - 1].table = table;
	table->philo[pos - 1].stats[POSTN] = pos;
	table->philo[pos - 1].stats[EATEN] = 0;
	table->philo[pos - 1].stats[LMEAL] = 0;
	table->philo[pos - 1].stats[START] = 0;
	sem_name(semaname, CLOCK, pos);
	table->philo[pos - 1].clock = sem_open(semaname, O_CREAT, 0600, 1);
	return (table->philo[pos -1].clock != SEM_FAILED);
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
		if (!a_wild_philosopher_appears(table, pos))
			return (false);
		pos++;
	}
	return (true);
}

//
static bool table_semaphores(t_tabl *table)
{
//	unlink_semaphores();
    table->semaphores[F0RK] = sem_open(FORKS, O_CREAT, 0600,\
			table->params[CNT]);
   	if (table->semaphores[F0RK] == SEM_FAILED) 
		return (false);	
	table->semaphores[MONT] = sem_open(MONIT, O_CREAT, 0600, 1);
   	if (table->semaphores[MONT] == SEM_FAILED) 
		return (false);	
    table->semaphores[BEGN] = sem_open(BEGIN, O_CREAT, 0600, 0);
   	if (table->semaphores[BEGN] == SEM_FAILED) 
		return (false);
    table->semaphores[DEID] = sem_open(DEATH, O_CREAT, 0600, 0);
   	if (table->semaphores[DEID] == SEM_FAILED) 
		return (false);
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
	table->sim = false;
	table->philo = NULL;
	table->params[STS] = -1;
	table->semaphores[F0RK] = NULL;
	table->semaphores[MONT] = NULL;
	table->semaphores[BEGN] = NULL;
	while (index < TABLES)
	{
		temp = my_atoi(argv[index]);
		if (temp < 0)
			return (false);	
		table->params[index] = temp;
		index++;
	}
	return (table_semaphores(table));
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
