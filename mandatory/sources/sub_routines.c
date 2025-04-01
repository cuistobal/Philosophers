/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 15:22:16 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// *rompiche intensifies*
void	sleeping(t_phil *philosopher)
{
	long	sleep_time;

	pthread_mutex_lock(&philosopher->clock);
	sleep_time = philosopher->table->params[SLP];
	pthread_mutex_unlock(&philosopher->clock);
	status(philosopher, SLEP);
	usleep(sleep_time * MSEC);
}

// *scronch scronch scronch*
void	eating(t_phil *philosopher)
{
	long	meal_time;

	pthread_mutex_lock(philosopher->lfork);
	status(philosopher, FORK);
	pthread_mutex_lock(philosopher->rfork);
	status(philosopher, FORK);
	pthread_mutex_lock(&philosopher->clock);
	meal_time = philosopher->table->params[EAT];
	philosopher->stats[LMEAL] = get_timestamp();
	philosopher->stats[EATEN]++;
	pthread_mutex_unlock(&philosopher->clock);
	status(philosopher, EATS);
	usleep(meal_time * MSEC);
	pthread_mutex_unlock(philosopher->lfork);
	pthread_mutex_unlock(philosopher->rfork);
}

static long	my_min(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

//The philos are right handed if an even number sits around the table. They 
//become left handed otherwise.
void	thinking(t_phil	*philosopher)
{
	long	think_time;

	pthread_mutex_lock(&philosopher->clock);
	think_time = my_min(philosopher->table->params[EAT], philosopher->table->params[SLP]);
	pthread_mutex_unlock(&philosopher->clock);
	status(philosopher, THNK);
	usleep(think_time * MSEC);
}
