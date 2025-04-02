/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/02 10:12:39 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
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
			(*full)++;
	}
	return (true);
}
*/

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
	end = table->params[END];
    while (table->simulation || full < table->params[CNT])
	{
		index = 0;
		while (index < table->params[CNT])
		{
            if (full == table->params[CNT])
			{
				status(&table->philo[index], DIED);
				break ;
			}
			/*
			if (!dead_or_full(&table->philo[index], &full, end) || full == table->params[CNT])
			{
				table->simulation = false;
				break ;
			}
            */
            if (you_are_dead(&table->philo[index]))
            {
				table->simulation = false;
            //    status(&table->philo[index], DIED);
                break ;
            }
            if (table->philo[index].stats[EATEN] == end)
                full++;
			index++;
		}
	}
	pthread_mutex_unlock(&table->monitoring);
	return (NULL);
}
