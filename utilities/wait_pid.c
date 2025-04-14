/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:38:26 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 12:58:18 by chrleroy         ###   ########.fr       */
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
	table->sim = false;
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
	//	int count)
{
	pid_t	pid;
	int		index;
	int		status;
	int		finished;

	index = 0;
	finished = 0;
	while (table->sim)
	{
		pid = waitpid(0, &status, WNOHANG);
		if (pid == 0)
			continue ;
		else if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == DEID)	
				return (death(table));	
			else if (WEXITSTATUS(status) == FULL)	
				printf("Philo %d iss full of pasta\n", index);
			finished++;	
		}
		index++;
	}
	return (finished == table->params[CNT]);
}

/*
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
*/
