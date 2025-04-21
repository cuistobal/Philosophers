/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:58:40 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/21 14:21:35 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static const char *semanames[SEMP] = {FORKS, MONIT, DEATH};

//
void    kill_philos(t_phil *philo, int pcount)	
{
	int index;

	index = 0;
	while (index < pcount)	
	{
		kill(philo[index].pid, SIGINT);
		index++;
	}
}

//
static void	clean_philos(t_tabl *table)
{
	int		index;

	index = 0;
	while (index < (table)->params[CNT])
	{
		if ((table)->philo[index].clock)
		{
			sem_close((table)->philo[index].clock);
			sem_unlink((table)->philo[index].semaname);
			(table)->philo[index].clock = NULL;
		}
		index++;
	}
}

//
static void	clean_table(t_tabl *table)
{
	int	index;

	index = 0;
	while (index < SEMP)
	{
		if ((table)->semaphores[index] != NULL && \
				(table)->semaphores[index] != SEM_FAILED)
		{
			sem_close((table)->semaphores[index]);
			sem_unlink(semanames[index]);
			(table)->semaphores[index] = NULL;	
		}	
		index++;
	}	
}

//
void	cleanup_bonus(t_tabl *table, char *message)
{
	int	index;

	index = 0;
	if (table)
	{	
		if ((table)->philo)
		{
			clean_philos(table);
			free((table)->philo);
			(table)->philo = NULL;
		}
		clean_table(table);
		free(table);
		table = NULL;
		if (message)
			printf("%s\n", message);
	}
}
