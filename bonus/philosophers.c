/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 11:36:55 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static void	init_processes(t_tabl *table)
{
	int		index;

	index = 0;
	table->params[STS] = get_timestamp();
	while (index < table->params[CNT])
	{
		if (!create_child_process(table, index))	
			cleanup_bonus(table, FORK_ERROR);
		index++;
	}
	table->params[STS] = get_timestamp();
	index = 0;
	while (index < table->params[CNT])
	{
		sem_post(table->semaphores[BEGN]);
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
			init_processes(table);
			if (waiter(table))
				return (cleanup_bonus(table, SUCCESS), 0);
			return (cleanup_bonus(table, "ECHEEEEEC DE LA QUETE"), 0);
		}
		return (cleanup_bonus(table, INIT_TABLE), 0);
	}
	return (cleanup_bonus(table, ARGC), 0);
}
