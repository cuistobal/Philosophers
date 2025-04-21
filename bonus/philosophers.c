/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/21 15:26:20 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static bool	wait_for_childs(t_tabl *table)
{
	int	full;
	int	index;
	int	status;

	full = table->params[CNT];
	while (full > 0)
	{
		index = 0;
		full = table->params[CNT];
		while (index < table->params[CNT])
		{
			if (waitpid(table->philo[index].pid, &status, WNOHANG) != 0)
			{
				if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
				{
					kill_philos(table->philo, table->params[CNT]);
					return (sem_post(table->semaphores[DEAD]), false);
				}
				else if (WIFEXITED(status))
					full--;
			}
			index++;
		}
	}
	return (sem_post(table->semaphores[DEAD]), true);
}

//
static bool	init_processes(t_tabl *table)
{
	int		index;
	long	start;

	index = 0;
	start = get_timestamp() + table->params[CNT] * 10;
	table->params[STS] = start;
	while (index < table->params[CNT])
	{
		table->philo[index].stats[START] = start;
		table->philo[index].stats[LMEAL] = start;
		table->philo[index].pid = fork();
		if (table->philo[index].pid < 0)
			return (write(1, FORK_ERROR, my_strlen(FORK_ERROR)), false);
		else if (table->philo[index].pid == 0)
			routine(&table->philo[index]);
		index++;
	}
	return (true);
}

//
int	main(int argc, char **argv)
{
	bool	type;
	t_tabl	*table;

	table = NULL;
	if (argc != 5 && argc != 6)
		return (cleanup_bonus(table, ARGC), 0);
	if (!init_table(&table, argv))
		return (cleanup_bonus(table, INIT_TABLE), 0);
	if (!init_processes(table))
		return (cleanup_bonus(table, INIT_TABLE), 0);
	type = wait_for_childs(table);
	sem_wait(table->semaphores[DEAD]);
	if (type)
		write(1, SUCCESS, strlen(SUCCESS));
	return (cleanup_bonus(table, NULL), 0);
}
