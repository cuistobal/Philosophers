/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 11:24:50 by chrleroy         ###   ########.fr       */
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

//This is an accurate description of an hungover philosopher's routine. At
//first, they try to grab the fork on their left. If it fails, they pretend life
// and start regretting all this liquor ingested last night. Once they grab the
//fork, their focus shifts to grabbing the second fork.
//After ingesting all those spaghettis, they feel sleepy hence take a nap.
void	*routine(void *data)
{
	t_phil	*philo;

	philo = (t_phil *)data;

//	Start synchroniser

	sem_wait(philo->table->semaphores[BEGN]);

	philo->stats[START] = philo->table->params[STS];
	philo->stats[LMEAL] = philo->stats[START];
	
	sem_post(philo->table->semaphores[BEGN]);

//
	while (1)
	{
		if (philo->stats[POSTN] & 1)
			even_routine(philo);
		else
			uneven_routine(philo);
		if (philo->stats[EATEN] == philo->table->params[EAT])
			exit(FULL);
		else if (get_timestamp() - philo->stats[LMEAL] >= philo->table->params[DIE])
			exit(DEATH);
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
		return (false);	
	}
	else if (current > 0)
		philosopher->pid = current;
	else
		routine(philosopher);
	return (true);
}
