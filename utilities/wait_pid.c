/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:38:26 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/17 14:28:36 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
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
*/
//If the philosopher is full -> kill him with FULL signal
//If the philosopher is dead -> kill him with DEAD signal
//
//	If one of the philo died -> kill them all with a recursive call
//
//Sending and *index to take kill processes in case we get a wrong exti status
//void	waiter(t_tabl *table, int *index, bool *success)
bool	waiter(t_tabl *table)
{
//	pid_t	pid;
	int		index;
	int		status;
	int		finished;
	
	index = 0;
	finished = 0;
    while (finished != table->params[CNT])
    {
	    index = 0;
	    finished = 0;
	    while (index < table->params[CNT])
	    {
    		waitpid(table->philo[index].pid, &status, WNOHANG);
            if (WIFEXITED(status))
            {
                if (status > 1)
                    finished++;
          //  else
            //    death(table);
            //printf("finished %d index %d && status %d\n", finished, index, status);
            }
		/*
        pid = waitpid(table->philo[index].pid, &status, WNOHANG);	
		if (pid != 0 && WIFEXITED(status))
		{
            printf("status = %d\n", status);
			if (WEXITSTATUS(status) != 0 && WEXITSTATUS(status) != 1)
            {
                printf("You are ded %ld -> %d\n", table->philo[index].stats[POSTN], status);
				return (death(table));
            }
            finished++;	
		}
        */
		    index++;
	    }
        //printf("finished = %d\n", finished);
    }
	return (finished == table->params[CNT]);
}
