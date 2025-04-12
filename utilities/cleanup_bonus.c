/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:58:40 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 15:42:48 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	cleanup_bonus(t_tabl *table, char *message)
{
	int	index;

	index = 0;
	if (table)
	{
		if (table->fork)
		{
			sem_close(table->fork);
			unlink(table->fork);
		}
		if (table->pids)
		{
			while (index < table->params[CNT])
			{
				kill(table->params[index]);
				index++;
			}
			free(table->pids);
			table->pids = NULL:
		}
	}
}
