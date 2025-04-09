/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sub_routines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/09 10:31:14 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// *rompiche intensifies*
void	sleeping(t_phil *philosopher)
{
	if (the_show_must_go_on(philosopher))
	{
		status(philosopher, SLEP);
		my_usleep(philosopher, philosopher->table->params[SLP], \
				get_timestamp());
	}
}

//The philos are right handed if an even number sits around the table. They 
//become left handed otherwise.
void	thinking(t_phil	*philosopher)
{
	int	think;

	think = 1;
	if (the_show_must_go_on(philosopher))
	{
		/*
		pthread_mutex_lock(&philosopher->clock);
		if (get_timestamp() - philosopher->stats[LMEAL] > \
				philosopher->table->params[DIE] )
			think = ;
		pthread_mutex_unlock(&philosopher->clock);		
		*/
		status(philosopher, THNK);
		my_usleep(philosopher, think, get_timestamp());
	}
}
