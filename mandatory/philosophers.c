/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 15:49:25 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
static void	dinner_time(t_tabl *table)
{
	int	index;

	//init threads	

	index = 0;
	while (index < table->params[CNT])
	{
		if (pthread_create(&table->philo[index].thread, NULL, routine, \
				&table->philo[index]) != 0)
			cleanup(table, THREAD_CREATE);
		index++;
	}

	//set start timer && monitor execution

	pthread_mutex_lock(&table->monitoring);
	table->params[STS] = get_timestamp();
	pthread_create(&table->thread, NULL, alive_and_not_full, table);
	pthread_detach(table->thread);
	pthread_mutex_unlock(&table->monitoring);
	
	//join threads

	index = 0;
	while (index < table->params[CNT])
	{
		if (pthread_join(table->philo[index].thread, NULL) != 0)
			cleanup(table, THREAD_CREATE);
		index++;
	}
}

//
int	main(int argc, char **argv)
{
	t_tabl	*table;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		if (init_table(&table, argv))
		{
			dinner_time(table);
			return (cleanup(table, NULL));
		}
		return (cleanup(table, INIT_TABLE));
	}
	return (cleanup(table, ARGC));
}
