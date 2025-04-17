/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/17 14:15:51 by cuistobal        ###   ########.fr       */
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
//	void		*temp;
	t_tabl		*table;
	pthread_t	monitoring;

	table = NULL;
	if (argc != 5 && argc != 6)
		return (cleanup_bonus(table, ARGC), 0);
	if (!init_table(&table, argv))
		return (cleanup_bonus(table, INIT_TABLE), 0);
	
	init_processes(table);
	
//    temp = NULL;
	pthread_create(&monitoring, NULL, child_monitor, table);	
	pthread_join(monitoring, NULL);
    int i = 0;
    for (i = 0; i < table->params[CNT]; i++)
        sem_wait(table->semaphores[FULL]);
    if (i == table->params[CNT])
        printf("all full\n");
    else
        printf("Someone died\n");
//	if (!temp)
//		return (cleanup_bonus(table, NULL), 0);
//    pthread_detach(moniitoring); 
	for (int i= 0; i < table->params[CNT]; i++)
		kill(table->philo[i].pid, SIGINT);
	return (cleanup_bonus(table, SUCCESS), 0);
}
