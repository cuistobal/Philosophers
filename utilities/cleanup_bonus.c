/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:58:40 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/19 11:54:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static const char *semanames[SEMP] = {FORKS, MONIT, DEATH};

//
static void	kill_philos(t_phil *philo, int pcount)	
{
	int index;

	index = 0;
	while (index < pcount)	
	{
		kill(philo[index].pid, SIGINT);
		sem_close(philo[index].clock);
		sem_unlink(philo[index].semaname);
		philo[index].clock = NULL;
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
		if (table->philo)
		{
			kill_philos(table->philo, table->params[CNT]);
		//	sema_cleanup(table->philo, table->params[CNT]);
			free(table->philo);
			table->philo = NULL;
		}
		while (index < SEMP)
		{
			sem_close(table->semaphores[index]);
			sem_unlink(semanames[index]);
			index++;
		}
		free(table);
		table = NULL;
		if (message)
			printf("%s\n", message);
	}
}
