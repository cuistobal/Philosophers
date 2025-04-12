/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:38:26 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 14:32:15 by chrleroy         ###   ########.fr       */
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
bool	waiter(pid_t *pids, int count)
{
	bool	end;
	int		index;
	int		status;
	int		finished;

	index = 0;
	finished = 0;
	while (index < count)
	{
		waitpid(pids[index], &status, WNOHANG);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == DEATH)	
				printf("process %d died with status %d.\n", index, status);
			else if (WEXITSTATUS(status) == FULL)
				printf("process %d died with status %d.\n", index, status);
			else
				printf("%d	->	Process %d is over with status %d\n", index, pids[index], status);
			finished++;	
		}
		index++;
	}
	return (finished == count);
}

void	create_process(pid_t *pids,	int index)
{
	pid_t	current; 

	current = fork();
	if (current > 0)
		pids[index] = current;
	else if (current == 0)
		index == 7 ? (usleep(10000), exit(DEATH)) : index == 4 ? (usleep(1000), exit(FULL)) : (usleep(100), exit(SUCES));
}

//test
int main(int argc, char **argv)
{
	pid_t	*pids;
	pid_t	current;
	int		index = 0;

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
		while (!waiter(pids, count))
			continue ;
	}
}
