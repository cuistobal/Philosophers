/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:38:26 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/19 10:29:06 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//If the philosopher is full -> kill him with FULL signal
//If the philosopher is dead -> kill him with DEAD signal
//
//	If one of the philo died -> kill them all with a recursive call
//
//Sending and *index to take kill processes in case we get a wrong exti status
//void	waiter(t_tabl *table, int *index, bool *success)
bool	waiter(t_tabl *table)
{
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
                if (status < 0)
					break ;	
                finished++;
            }
		    index++;
	    }
		if (finished == table->params[CNT])
			break ;
		usleep(TCAP);
    }
	return (finished == table->params[CNT]);
}
