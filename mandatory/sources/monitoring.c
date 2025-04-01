/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 13:03:48 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
static bool	dead_or_full(t_phil *philo, int *full, int end)
{
	if (you_are_dead(philo))
		return (false);
	if (end >= 0)
	{
		printf("%ld / %d\n", philo->stats[EATEN], end);
		if (philo->stats[EATEN] == end)
			full++;
	}
	return (true);
}

//This function checks my boi did not starve not got enough pasta. 
bool	alive_and_not_full(t_tabl *table)
{
	int		end;
	int		full;
	int		index;

	full = 0;
	pthread_mutex_lock(&table->monitoring);
	end = table->params[DIE];
	pthread_mutex_unlock(&table->monitoring);
	while (1)
	{
		index = 0;
		pthread_mutex_lock(&table->monitoring);
		while (index < table->params[CNT])
		{
			if (dead_or_full(&table->philo[index], &full, end))
			{
				status(table->philo, DIED);
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
