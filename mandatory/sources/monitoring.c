/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 14:16:23 by chrleroy         ###   ########.fr       */
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
		if (philo->stats[EATEN] == end)
			full++;
	}
	return (true);
}

//This function checks my boi did not starve not got enough pasta. 
void	*alive_and_not_full(void *data)
{
	int		end;
	int		full;
	int		index;
	t_tabl	*table;

	full = 0;
	table = (t_tabl *)data;
	pthread_mutex_lock(&table->monitoring);
	end = table->params[DIE];
	pthread_mutex_unlock(&table->monitoring);
	while (1)
	{
		index = 0;
		pthread_mutex_lock(&table->monitoring);
		while (index < table->params[CNT])
		{
			if (!dead_or_full(&table->philo[index], &full, end))
			{
				status(&table->philo[index], DIED);
				pthread_mutex_unlock(&table->monitoring);
				return ((void *)false);
			}
			index++;
		}
		if (full == table->params[CNT])
		{
			pthread_mutex_unlock(&table->monitoring);
			break ;
		}
		pthread_mutex_unlock(&table->monitoring);
	}
	return ((void *)true);
}
