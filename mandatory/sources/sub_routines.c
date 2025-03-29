/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/29 12:07:23 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// *rompiche intensifies*
void	sleeping(t_phil *philosopher)
{
	long	sleep_time;

	pthread_mutex_lock(&philosopher->table->monitoring);
	sleep_time = philosopher->table->params[SLP];
	pthread_mutex_unlock(&philosopher->table->monitoring);
	status(philosopher, SLEP);
	usleep(sleep_time);
}

// *scronch scronch scronch*
void	eating(t_phil *philosopher)
{
	long	meal_time;

	pthread_mutex_lock(philosopher->lfork);
	status(philosopher, FORK);
	pthread_mutex_lock(philosopher->rfork);
	status(philosopher, FORK);
	pthread_mutex_lock(&philosopher->table->monitoring);
	meal_time = philosopher->table->params[EAT];
	philosopher->stats[LMEAL] = get_timestamp();
	philosopher->stats[EATEN]++;
	pthread_mutex_unlock(&philosopher->table->monitoring);
	status(philosopher, EATS);
	usleep(meal_time);
	pthread_mutex_unlock(philosopher->lfork);
	pthread_mutex_unlock(philosopher->rfork);
}

//The philos are right handed if an even number sits around the table. They 
//become left handed otherwise.
void	thinking(t_phil	*philosopher)
{	
	status(philosopher, THNK);
	usleep(100);
}
