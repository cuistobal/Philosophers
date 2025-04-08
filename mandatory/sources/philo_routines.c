/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/08 12:11:29 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
static void	even_routine(t_phil *philo, bool even)
{
	eating(philo, even);
	sleeping(philo);
	thinking(philo);
}

//
static void	uneven_routine(t_phil *philo, bool even)
{
	thinking(philo);
	eating(philo, even);
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

//Spinlock function to synchronise the threads start.
static void	starting_block(t_phil *philo)
{
	pthread_mutex_lock(&philo->clock);
	pthread_mutex_lock(&philo->table->monitoring);
	while (philo->table->params[STS] == -1)
	{
		pthread_mutex_unlock(&philo->table->monitoring);
		usleep(10);
		pthread_mutex_lock(&philo->table->monitoring);
	}
	pthread_mutex_unlock(&philo->table->monitoring);
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
	while (the_show_must_go_on(philo))
	{
		if (even)
			even_routine(philo, even);
		else
			uneven_routine(philo, even);
	}
	return (NULL);
}
