/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 11:50:14 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

//
static bool	is_even(t_phil *philo)
{
	long	position;

	pthread_mutex_lock(&philo->clock);
	position = philo->stats[POSTN];
	pthread_mutex_unlock(&philo->clock);
	return (position & 1);
}

//Recursive spinlock function to synchronise the threads start.
static void	starting_block(t_phil *philo)
{
	pthread_mutex_lock(&philo->clock);
	while (philo->table->params[STS] == -1)
		;
	philo->stats[START] = philo->table->params[STS];
	philo->stats[LMEAL] = philo->stats[START];
	pthread_mutex_unlock(&philo->clock);
}

//This is an accurate description of an hungover philosopher's routine. At 
//first, they try to grab the fork on their left. If it fails, they pretend life
// and start regretting all this liquor ingested last night. Once they grab the
//fork, their focus shifts to grabbing the second fork.
//After ingesting all those spaghettis, they feel sleepy hence take a nap. 
void	*routine(void *philosopher)
{
	bool	even;
	t_phil	*philo;

	philo = (t_phil *)philosopher;
	even = is_even(philo);
	starting_block(philo);
	while (!you_are_dead(philo))
	{
	//	if (you_are_dead(philo))
	//		break ;
		if (even)
			even_routine(philo);
		else
			uneven_routine(philo);
	}
	return (NULL);
}
