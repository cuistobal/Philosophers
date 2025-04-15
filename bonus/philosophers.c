/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/15 19:05:36 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*child_monitor(void *data)
{
	t_tabl	*table;

	table = (t_tabl *)data;
	while (table->sim)
	{
		if (waiter(table))
			return (data);
		usleep(TCAP);	
	}
	return (NULL);
}

//
static bool	init_processes(t_tabl *table)
{
	int			index;
	
	index = 0;
	table->params[STS] = get_timestamp() + table->params[CNT] * 10;
	while (index < table->params[CNT])
	{
		if (!create_child_process(&table->philo[index]))
			return (false);
		index++;
	}
	sem_post(table->semaphores[BEGN]);
	return (true);
}

//
int	main(int argc, char **argv)
{
	void		*temp;
	t_tabl		*table;
	pthread_t	monitoring;

	table = NULL;
	if (argc != 5 && argc != 6)
		return (cleanup_bonus(table, ARGC), 0);
	if (!init_table(&table, argv))
		return (cleanup_bonus(table, INIT_TABLE), 0);
	
	init_processes(table);
	
	pthread_create(&monitoring, NULL, child_monitor, table);	
	pthread_join(monitoring, &temp);
	if (!temp)
		return (cleanup_bonus(table, NULL), 0);

	for (int i= 0; i < table->params[CNT]; i++)
		kill(table->philo[i].pid, SIGINT);
	return (cleanup_bonus(table, SUCCESS), 0);
}
