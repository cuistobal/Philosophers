/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:38:26 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/15 19:09:50 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static bool	death(t_tabl *table)
{
	int	index;

	index = 0;
	while (index < table->params[CNT])
	{
		kill(table->philo[index].pid, SIGINT);
		index++;
	}
	sem_wait(table->semaphores[BEGN]);
	table->sim = false;
	sem_post(table->semaphores[BEGN]);
	return (true);
}

//If the philosopher is full -> kill him with FULL signal
//If the philosopher is dead -> kill him with DEAD signal
//
//	If one of the philo died -> kill them all with a recursive call
//
//Sending and *index to take kill processes in case we get a wrong exti status
//void	waiter(t_tabl *table, int *index, bool *success)
bool	waiter(t_tabl *table)
{
	pid_t	pid;
	int		index;
	int		status;
	int		finished;
	
	index = 0;
	finished = 0;
	while (index < table->params[CNT])
	{
		pid = waitpid(table->philo[index].pid, &status, WNOHANG);	
		if (pid != 0 && WIFEXITED(status))
		{
			if (WEXITSTATUS(status))
				return (death(table));
			finished++;	
		}
		index++;
	}
	return (finished == table->params[CNT]);
}
