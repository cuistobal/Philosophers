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

//
static bool	dead_or_full(t_tabl *table, t_phil *philo, int *full)
{
	long	end;
	long	eaten;

	end = table->params[DIE];
	if (you_are_dead(philo))
		return (false);
	if (end >= 0)
	{
		eaten = philo->stats[EATEN];
		if (eaten == end)
			full++;
	}
	return (true);
}

//This function checks my boi did not starve not got enough pasta. 
bool	alive_and_not_full(t_tabl *table)
{
	int		full;
	int		index;

	full = 0;
	while (1)
	{
		index = 0;
		pthread_mutex_lock(&table->monitoring);
		while (index < table->params[CNT])
		{
			if (dead_or_full(table, &table->philo[index], &full))
			{
				pthread_mutex_unlock(&table->monitoring);
				return (false);
			}
			index++;
		}
		pthread_mutex_unlock(&table->monitoring);
		if (full == table->params[CNT])
			break ;
	}
	return (true);
}
