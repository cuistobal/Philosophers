/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/03 13:59:50 by chrleroy         ###   ########.fr       */
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
		while (index < table->params[CNT])
		{
			pthread_mutex_destroy(&table->fork[index]);
			index++;
		}
		if (table->fork)
		{
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
