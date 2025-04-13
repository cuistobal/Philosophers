/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:58:40 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/13 09:57:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//Include the sem_name to unlink()
static void	destroy_semaphore(sem_t	*semaphore)
{
	sem_close(semaphore);
//	unlink(semaphore);
}

void	cleanup_bonus(t_tabl *table, char *message)
{
	int	index;

	index = 0;
	if (table)
	{
		while (index < SEMP)
		{
			destroy_semaphore(&table->semaphores[index]);
			index++;
		}
		index = 0;
		if (table->pids)
		{
			while (index < table->params[CNT])
			{
				kill(table->pids[index], SIGKILL);
				index++;
			}
			free(table->pids);
			table->pids = NULL;
		}
		if (message)
			printf("%s\n", message);
	}
}
