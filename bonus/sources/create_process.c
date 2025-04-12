/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 14:50:53 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	create_process(t_tabl *table, int index)
{
	pid_t	current;

	current	= fork();
	if (current < 0)
	{
		printf(FORK_ERROR);
		exit(F0RK_ERROR);
	}
	else if (fork > 0)
		table->pids[index] = current;
	else
	{
		routine(table->philo[index]);
	}
