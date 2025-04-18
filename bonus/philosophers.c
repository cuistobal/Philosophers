/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/18 09:19:14 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
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
    int	    index;
    long    start;
	
	index = 0;
    sem_wait(table->semaphores[BEGN]);
    start = get_timestamp() + table->params[CNT] * 10;
    table->params[STS] = start;
	while (index < table->params[CNT])
	{
        table->philo[index].stats[START] = start;
        table->philo[index].stats[LMEAL] = start;
		if (!create_child_process(&table->philo[index]))
			return (false);
		index++;
	}
    return (true);
}

//
int	main(int argc, char **argv)
{
	void		*temp;
	t_tabl		*table;
	pthread_t	monitoring_thread;

	table = NULL;
	if (argc != 5 && argc != 6)
		return (cleanup_bonus(table, ARGC), 0);
	if (!init_table(&table, argv))
		return (cleanup_bonus(table, INIT_TABLE), 0);
	
	init_processes(table);
	
    temp = NULL;
	pthread_create(&monitoring_thread, NULL, child_monitor, table);	
	pthread_join(monitoring_thread, &temp);
	if (!temp)
		return (cleanup_bonus(table, NULL), 0);
//	for (int i= 0; i < table->params[CNT]; i++)
//		kill(table->philo[i].pid, SIGINT);
	return (cleanup_bonus(table, SUCCESS), 0);
}
