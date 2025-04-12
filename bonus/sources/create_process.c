/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 16:21:14 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	routine(t_phil *philo)
{
	while (true)
	{
		if (philo->id & 1)
		{
			eating();
			sleeping();
			thinking();
		}
		else
		{
			eating();
			sleeping();
			thinking();
		}
	}
}

bool	create_child_process(t_phil *philo, pid_t *pid)
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
		routine(philo);
}
