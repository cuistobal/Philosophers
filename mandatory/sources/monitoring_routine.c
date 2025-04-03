/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/03 10:00:14 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
bool	you_are_dead(t_phil *philo)
{
	long	die;
	long	last_meal;

	pthread_mutex_lock(&philo->clock);
	last_meal = philo->stats[LMEAL];
	die = philo->table->params[DIE];
	pthread_mutex_unlock(&philo->clock);
	return ((get_timestamp() - last_meal) >= die);
}

//
bool	you_are_full(t_tabl *table, t_phil *philo)
{
	long	eaten;

	pthread_mutex_lock(&table->monitoring);
	eaten = philo->stats[EATEN];
	pthread_mutex_unlock(&table->monitoring);
	return (eaten >= table->params[END]);
}

void	*stop_simulation(t_tabl *table, t_phil *philo, bool flag)
{
	pthread_mutex_lock(&table->monitoring);
	table->simulation = false;
	if (flag)
		status(philo, DIED);
	pthread_mutex_unlock(&table->monitoring);	
	return (NULL);
}
//
void	*monitoring(void *data)
{
	int		full;
	int		index;
	t_tabl	*table;

	table = (t_tabl *)data;
	while (table->simulation)
//	while (1)
	{
		full = 0;
		index = 0;
		while (index < table->params[CNT])
		{
			if (you_are_dead(&table->philo[index]))
				return (stop_simulation(table, &table->philo[index], true));	
			/*
			{
				pthread_mutex_lock(&table->monitoring);
				table->simulation = false;
				status(&table->philo[index], DIED);	
				pthread_mutex_unlock(&table->monitoring);	
				break ;
			}
			*/
			if (you_are_full(table, &table->philo[index]))
				full++;
			index++;
		}
        if (full == table->params[CNT])	
			return (stop_simulation(table, &table->philo[index], false));	
		/*
		{
			pthread_mutex_lock(&table->monitoring);
			table->simulation = false;
			pthread_mutex_unlock(&table->monitoring);	
			break ;
		}
		*/
		usleep(MSEC);
	}
	return (NULL);
}
