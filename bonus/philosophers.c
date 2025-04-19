/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/19 14:34:31 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static bool	init_processes(t_tabl *table)
{
    int	    index;
    long    start;
	
	index = 0;
    start = get_timestamp() + table->params[CNT] * 10;
    table->params[STS] = start;
	while (index < table->params[CNT])
	{
        table->philo[index].stats[START] = start;
        table->philo[index].stats[LMEAL] = start;

		table->philo[index].pid = fork();
		if (table->philo[index].pid < 0)
		{
			printf(FORK_ERROR);
			return (false);
		}
		else if (table->philo[index].pid == 0)
			exit(routine(&table->philo[index]));
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

	sem_wait(table->semaphores[DEAD]);

	if (table->sim)
		return (cleanup_bonus(table, SUCCESS), 0);
	return (cleanup_bonus(table, NULL), 0);
}
