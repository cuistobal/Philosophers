/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/18 10:26:05 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
	t_tabl		*table;

	table = NULL;
	if (argc != 5 && argc != 6)
		return (cleanup_bonus(table, ARGC), 0);
	if (!init_table(&table, argv))
		return (cleanup_bonus(table, INIT_TABLE), 0);
	
	if (!init_processes(table))
		return (cleanup_bonus(table, INIT_TABLE), 0);	
	
	while (waiter(table))
		;
	return (cleanup_bonus(table, SUCCESS), 0);
}
