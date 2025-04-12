/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:38:26 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 14:08:16 by chrleroy         ###   ########.fr       */
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

// int count = 0;

# define SUCES 0
# define FULL 17
# define DEATH 120

//If the philosopher is full -> kill him with FULL signal
//If the philosopher is dead -> kill him with DEAD signal
//
//	If one of the philo died -> kill them all with a recursive call
//
//Sending and *index to take kill processes in case we get a wrong exti status
//void	waiter(t_tabl *table, int *index, bool *success)
void	waiter(pid_t *pids, int *index, bool *success, int count)
{
	int		status;

//	while (*index < table->params[CNT])
	while (*index < count)
	{
		if (!*success)
		{
			//kill(table->pids[*index], DEAD);
			if (kill(pids[*index], DEATH) == 0)
				printf("Killed process %d.\n", *index);
		}
		else
		{
		//	waitpid(table->pids[index], &status, 0)
			waitpid(pids[*index], &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) == DEATH)
			{
			//	status(table->philosopher[*index], DIED);
				printf("process %d died with status %d.\n", *index, status);	
				*success = false;
				*index = 0;
			//	waiter(table, index, success);
				waiter(pids, index, success, count);
			}
			else if (WIFEXITED(status) && WEXITSTATUS(status) == FULL)
			//	kill(table->pids[*index], FULL);
				kill(pids[*index], FULL);
			else
				printf("%d	->	Process %d is over with status %d\n", *index, pids[*index], status);
		}
		(*index)++;
	}
}

void	create_process(pid_t *pids,	int index)
{
	pid_t	current; 

	current = fork();
	if (current > 0)
		pids[index] = current;
	else if (current == 0)
		index == 7 ? exit(DEATH) : index == 4 ? exit(FULL) : exit(SUCES);
	else
		printf("FAILED\n");
}

//test
int main(int argc, char **argv)
{
	pid_t	*pids;
	pid_t	current;
	int		index = 0;
	bool sucess = true;

	if (argc == 2)
	{
		int count = atoi(argv[1]);
		pids = malloc(sizeof(pid_t) * count);
		if (!pids)
			return -1;
		memset(pids, -1, sizeof(pid_t) * count);
		while (index < count)
		{
			create_process(pids, index);
			index++;
		}
		index = 0;
		waiter(pids, &index, &sucess, count);
	}
}
