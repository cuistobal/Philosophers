/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/15 11:23:15 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*monitoring(void *data)
{
	t_phil	*philo;

	philo = (t_phil *)data;
	while (1)
	{
		sem_wait(philo->table->semaphores[DEAD]);
		if (philo->stats[EATEN] == philo->table->params[EAT])
			return((void *)FULL);
		else if (get_timestamp() - philo->stats[LMEAL] >= philo->table->params[DIE])
			return((void *)DEATH);
		sem_post(philo->table->semaphores[DEAD]);
		usleep(TCAP);
	}
	return (NULL);
}

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

//This is an accurate description of an hungover philosopher's routine. At
//first, they try to grab the fork on their left. If it fails, they pretend life
// and start regretting all this liquor ingested last night. Once they grab the
//fork, their focus shifts to grabbing the second fork.
//After ingesting all those spaghettis, they feel sleepy hence take a nap.
int	routine(t_phil *philo)
{
	pthread_t	monitor;

	sem_wait(philo->table->semaphores[BEGN]);

	philo->stats[START] = philo->table->params[STS];
	philo->stats[LMEAL] = philo->stats[START];
	
	sem_post(philo->table->semaphores[BEGN]);

	pthread_create(&monitor, NULL, monitoring, philo);
	pthread_detach(monitor);
	while (1)
	{
		if (philo->stats[POSTN] & 1)
			even_routine(philo);
		else
			uneven_routine(philo);
		/*
		if (philo->stats[EATEN] == philo->table->params[EAT])
			return(FULL);
		else if (get_timestamp() - philo->stats[LMEAL] >= philo->table->params[DIE])
			return(DEID);
	*/
	}
	return (MEM);
}


//
void	create_child_process(t_tabl *table, int index)
{
	int		exit_code;
	t_phil	*philosopher;

	exit_code = 0;
	philosopher = &table->philo[index];
	philosopher->pid = fork();
	if (philosopher->pid < 0)
	{
		printf(FORK_ERROR);
		exit(MEM);
	}
	else if (philosopher->pid == 0)
	{
		exit_code = routine(philosopher);
		exit(exit_code);
	}
}
