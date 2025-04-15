/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/15 15:11:30 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static bool	init_processes(t_tabl *table)
{
	int			index;
	
	index = 0;
	while (index < table->params[CNT])
	{
		if (!create_child_process(&table->philo[index]))
			return (false);
		index++;
	}
	table->params[STS] = get_timestamp();
	sem_post(table->semaphores[BEGN]);
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
	
	init_processes(table);

	while (table->sim)
	{	
		if (waiter(table))
			return (cleanup_bonus(table, SUCCESS), 0);
	//	printf("THe show must go on.\n");
	}

}
