/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 09:21:26 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
static bool	free_table(t_tabl *table)
{
	int	index;

	index = 0;
	if (table)
	{
		if (table->fork)
		{
			while (index < table->params[CNT])
			{
				pthread_mutex_destroy(&table->fork[index]);
				index++;
			}
			free(table->fork);
			table->fork = NULL;
		}
		if (table->philo)
		{
			free(table->philo);
			table->philo = NULL;
		}
		free(table);
		table = NULL;
	}
	return (false);
}

//
bool	cleanup(t_tabl *table, char *message)
{
	if (message)
		printf("%s\n", message);
	return (free_table(table));
}
