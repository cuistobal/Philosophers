/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:38:26 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 13:26:16 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "philosophers_bonus.h"

# include <ctype.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <stdarg.h>
# include <unistd.h>
#include <sys/wait.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

int count = 0;

# define FULL 0
# define DEATH 1

//If the philosopher is full -> kill him with FULL signal
//If the philosopher is dead -> kill him with DEAD signal
//
//	If one of the philo died -> kill them all with a recursive call
//
//Sending and *index to take kill processes in case we get a wrong exti status
//void	waiter(t_tabl *table, int *index, bool *success)
void	waiter(pid_t *pids, int *index, bool *success)
{
	int		status;

//	while (*index < table->params[CNT])
	while (*index < count)
	{
		if (!*success)
			//kill(table->pids[*index], DEAD);
			kill(pids[*index], DEATH);
		else
		{
		//	waitpid(table->pids[index], &status, 0)
			waitpid(pids[*index], &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) == DEATH)
			{
			//	status(table->philosopher[*index], DIED);
				printf("process %d died.", *index);	
				*success = false;
				*index = 0;
			//	waiter(table, index, success);
				waiter(pids, index, success);
			}
			else if (WIFEXITED(status) && WEXITSTATUS(status) == FULL)
			//	kill(table->pids[*index], FULL);
				kill(pids[*index], FULL);
		}
		(*index)++;
	}
}

//test
int main(int argc, char **argv)
{
	pid_t	*pids;
	pid_t	current;
	int		index = 0;

	if (argc == 2)
	{
		count = atoi(argv[1]);
		pids = malloc(sizeof(pid_t) * count);
		if (!pids)
			return -1;
		while (index < count)
		{
			current = fork();
			if (current < 0)
				return -1;
			else if (current > 0)
				pids[index] = fork();	
			else
			{
				usleep(rand());
				exit(0);
			}
		}
		index = 0;
		bool sucess = true;
		waiter(pids, &index, &sucess);
	}
}
