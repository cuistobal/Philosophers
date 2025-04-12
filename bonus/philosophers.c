/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 16:15:42 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static void	set_monitoring(t_tabl *table)
{

}

//
static void	init_processes(t_tabl *table)
{
	int		index;
	t_phil	*philo;

	index = 0;
	philo = table->philo;
	while (index < table->params[CNT])
	{
		if (!create_child_process(&table->pids[index]))	
			cleanup_bonus(table, FORK_ERROR);
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
			set_monitoring(table);
			while (!waiter(table->pids, table->params[CNT]))
				continue ;
	/*
	 * Gestion des morts
	 */
			return (cleanup_bonus(table, NULL));
		}
		return (cleanup_bonus(table, INIT_TABLE));
	}
	return (cleanup_bonus(table, ARGC));
}
