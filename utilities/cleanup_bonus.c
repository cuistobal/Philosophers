/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:58:40 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 09:58:50 by chrleroy         ###   ########.fr       */
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
		index = 0;
		if (table->philo)		
		{
			index = 0;
			while (index < table->params[CNT])
			{
				sem_close(table->philo[index].clock);
				sem_unlink(table->philo[index].semaname);
				index++;
			}
			free(table->philo);
			table->philo = NULL;
		}
		printf("%s\n", message);
	}
}
