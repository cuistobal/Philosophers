/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sub_routines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/03 11:22:22 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// *rompiche intensifies*
void	sleeping(t_phil *philosopher)
{
/*
	long	sleep_time;

	pthread_mutex_lock(&philosopher->clock);
	sleep_time = philosopher->table->params[SLP];
	pthread_mutex_unlock(&philosopher->clock);
	status(philosopher, SLEP);
	usleep(sleep_time * MSEC);
*/
	if (the_show_must_go_on(philosopher))
	{
		status(philosopher, SLEP);
		my_usleep(philosopher, philosopher->table->params[SLP], get_timestamp());
	}
}

// *scronch scronch scronch*
void	eating(t_phil *philosopher)
{
	long	meal_start;

	if (the_show_must_go_on(philosopher))
	{
		pthread_mutex_lock(philosopher->lfork);
		status(philosopher, FORK);
		pthread_mutex_lock(philosopher->rfork);
		status(philosopher, FORK);

		pthread_mutex_lock(&philosopher->clock);
		philosopher->stats[LMEAL] = get_timestamp();
		meal_start = philosopher->stats[LMEAL];
		philosopher->stats[EATEN]++;
		pthread_mutex_unlock(&philosopher->clock);

		status(philosopher, EATS);
		my_usleep(philosopher, philosopher->table->params[EAT], meal_start);
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
	}
}

//The philos are right handed if an even number sits around the table. They 
//become left handed otherwise.
void	thinking(t_phil	*philosopher)
{
//	long	think_time;
//	t_tabl	*table;

//	table = philosopher->table;
	if (the_show_must_go_on(philosopher))
	{
		pthread_mutex_lock(&philosopher->clock);
//		think_time = my_min(table->params[EAT], table->params[SLP]) / 2;
		pthread_mutex_unlock(&philosopher->clock);
		status(philosopher, THNK);
//		my_usleep(philosopher, think_time, get_timestamp());
		my_usleep(philosopher, 0, get_timestamp());
	}
}
