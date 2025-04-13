/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/13 17:02:27 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static void	even_routine(t_phil *philo)
{
	eating(philo);
	sleeping(philo);
	thinking(philo);
}

//
static void	uneven_routine(t_phil *philo)
{
	thinking(philo);
	eating(philo);
	sleeping(philo);
}

//Spinlock function to synchronise the threads start.
static void	starting_block(t_phil *philo)
{
	//sem_wait(BEGIN);
	
	sem_wait(philo->table->semaphores[BEGN]);

	philo->stats[START] = philo->table->params[STS];
	philo->stats[LMEAL] = philo->stats[START];

	sem_post(philo->table->semaphores[BEGN]);
	
	//sem_post(BEGIN);
}

//This is an accurate description of an hungover philosopher's routine. At
//first, they try to grab the fork on their left. If it fails, they pretend life
// and start regretting all this liquor ingested last night. Once they grab the
//fork, their focus shifts to grabbing the second fork.
//After ingesting all those spaghettis, they feel sleepy hence take a nap.
void	*routine(void *philosopher)
{
	t_phil	*philo;

	philo = (t_phil *)philosopher;
	starting_block(philo);
	while (1)
	{
		if (philo->stats[POSTN] & 1)
			even_routine(philo);
		else
			uneven_routine(philo);
	}
	return (NULL);
}


//
bool	create_child_process(t_tabl *table, int index)
{
	pid_t	current;
	t_phil	*philosopher;

	philosopher = &table->philo[index];
	current	= fork();
	if (current < 0)
	{
		printf(FORK_ERROR);
		exit(F0RK_ERROR);
	}
	else if (current > 0)
	{
		philosopher->pid = current;
		table->pids[index] = current;
	}
	else
	{
		philosopher->pid = current;
		routine(philosopher);
	}
	return true;
}
