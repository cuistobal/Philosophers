/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sub_routines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/15 19:08:28 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	eating(t_phil *philosopher)
{
	long	meal_start;
	
	sem_wait(philosopher->table->semaphores[F0RK]);
	status_bonus(philosopher, FORK);	
	sem_wait(philosopher->table->semaphores[F0RK]);		
	status_bonus(philosopher, FORK);	

	sem_wait(philosopher->clock);
	
	philosopher->stats[LMEAL] = get_timestamp();
	meal_start = philosopher->stats[LMEAL];
	philosopher->stats[EATEN]++;

	sem_post(philosopher->clock);
	
	status_bonus(philosopher, EATS);
	
	my_usl33p(philosopher, philosopher->table->params[EAT], meal_start);

	sem_post(philosopher->table->semaphores[F0RK]);
	sem_post(philosopher->table->semaphores[F0RK]);	
}

// *rompiche intensifies*
void	sleeping(t_phil *philosopher)
{
	status_bonus(philosopher, SLEP);
	my_usl33p(philosopher, philosopher->table->params[SLP], get_timestamp());
}

//The philos are right handed if an even number sits around the table. They 
//become left handed otherwise.
void	thinking(t_phil	*philo)
{
	long	think;

	think =	(philo->table->params[DIE] - \
				(philo->table->params[EAT] + philo->table->params[SLP])) >> 1;
	status_bonus(philo, THNK);
	my_usl33p(philo, think, get_timestamp());
}
