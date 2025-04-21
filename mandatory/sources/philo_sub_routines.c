/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sub_routines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/21 15:39:15 by chrleroy         ###   ########.fr       */
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
void	thinking(t_phil	*philo)
{
	long	think;

	think = 0;
	if (the_show_must_go_on(philo))
	{
		status(philo, THNK);
		think = (philo->table->params[DIE] - \
				(philo->table->params[EAT] + philo->table->params[SLP])) >> 1;
		my_usleep(philo, think, get_timestamp());
	}
}
