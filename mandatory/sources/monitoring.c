/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 15:35:00 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
static bool	dead_or_full(t_phil *philo, int *full, int end)
{
	if (you_are_dead(philo))
	{
		status(philo, DIED);
		return (false);
	}
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
	while (1)
	{
		index = 0;
		while (index < table->params[CNT])
		{
			if (!dead_or_full(&table->philo[index], &full, end))
		//	{
		//		table->simulation = false;
				break ;
		//	}
			index++;
		}
		if (full == table->params[CNT])
			break ;
	}
	pthread_mutex_unlock(&table->monitoring);
	return (NULL);
}
