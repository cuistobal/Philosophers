/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:58:40 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 10:13:39 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static const char *semanames[SEMP] = {FORKS, MONIT, BEGIN};

void	unlink_semaphores(void)
{
	int	index;

	index = 0;
	while (index < SEMP)
	{
		unlink(semanames[index]);
		index++;
	}
}

static void	sema_cleanup(t_phil *philo, int pcount)
{
	int	index;

	index = 0;
	while (index < pcount)
	{
		sem_close(philo[index].clock);
		sem_unlink(philo[index].semaname);
		philo[index].clock = NULL;
		index++;
	}
}
void	cleanup_bonus(t_tabl *table, char *message)
{
	int	index;

	index = 0;
	if (table)
	{	
		while (index < SEMP)
		{
			sem_close(table->semaphores[index]);
			sem_unlink(semanames[index]);
			index++;
		}
		if (table->philo)		
		{
			sema_cleanup(table->philo, table->params[CNT]);
			free(table->philo);
			table->philo = NULL;
		}
		free(table);
		table = NULL;
		printf("%s\n", message);
	}
}
