/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:03:21 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/09 17:06:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static void	join_threads(t_tabl *table)
{
	int		index;
	t_phil	*philo;

	index = 0;
	philo = table->philo;
	while (index < table->params[CNT])
	{
		if (pthread_join(philo[index].thread, NULL) != 0)
			cleanup(table, THREAD_CREATE);
		index++;
	}
}

//
static void	set_monitoring(t_tabl *table)
{
	pthread_mutex_lock(&table->monitoring);
	table->params[STS] = get_timestamp();
	pthread_create(&table->thread, NULL, monitoring, table);
	pthread_detach(table->thread);
	pthread_mutex_unlock(&table->monitoring);
}

//
static void	init_threads(t_tabl *table)
{
	int		index;
	t_phil	*philo;

	index = 0;
	philo = table->philo;
	while (index < table->params[CNT])
	{
		if (pthread_create(&philo[index].thread, NULL, routine, \
				&philo[index]) != 0)
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
			init_threads(table);
			set_monitoring(table);
			join_threads(table);
			return (cleanup(table, NULL));
		}
		return (cleanup(table, INIT_TABLE));
	}
	return (cleanup(table, ARGC));
}
