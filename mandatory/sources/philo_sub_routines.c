/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sub_routines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/03 12:37:12 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// *rompiche intensifies*
void	sleeping(t_phil *philosopher)
{
	if (the_show_must_go_on(philosopher))
	{
		status(philosopher, SLEP);
		my_usleep(philosopher, philosopher->table->params[SLP], get_timestamp());
	}
}

// *scronch scronch scronch*
void	eating(t_phil *philosopher, bool even)
{
	long	meal_start;

	if (the_show_must_go_on(philosopher))
	{
		if (even)
		{
			pthread_mutex_lock(philosopher->lfork);
			status(philosopher, FORK);
			pthread_mutex_lock(philosopher->rfork);
			status(philosopher, FORK);
		}
		else
		{
			pthread_mutex_lock(philosopher->rfork);
			status(philosopher, FORK);
			pthread_mutex_lock(philosopher->lfork);
			status(philosopher, FORK);
		}

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
	if (the_show_must_go_on(philosopher))
	{
		pthread_mutex_lock(&philosopher->clock);
		pthread_mutex_unlock(&philosopher->clock);
		status(philosopher, THNK);
		my_usleep(philosopher, 1, get_timestamp());
	}
}
