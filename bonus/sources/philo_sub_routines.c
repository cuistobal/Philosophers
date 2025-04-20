/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sub_routines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/20 09:17:26 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void pick_forks(t_phil *philosopher)
{
	sem_wait(philosopher->table->semaphores[F0RK]);
    if (!the_sh0w_must_go_on(philosopher->table))
        exit(2);
    status_bonus(philosopher, FORK);
	sem_wait(philosopher->table->semaphores[F0RK]);		
    if (!the_sh0w_must_go_on(philosopher->table))
        exit(2);
    status_bonus(philosopher, FORK);	
}

void	eating(t_phil *philosopher)
{
	long	meal_start;
	
    pick_forks(philosopher);

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
    if (!the_sh0w_must_go_on(philosopher->table))
        exit(2);
    else
    {
	    status_bonus(philosopher, SLEP);
	    my_usl33p(philosopher, philosopher->table->params[SLP], get_timestamp());
    }
}

//The philos are right handed if an even number sits around the table. They 
//become left handed otherwise.
void	thinking(t_phil	*philo)
{
	long	think;

    if (!the_sh0w_must_go_on(philo->table))
        exit(2);
    else
    {
        think =	(philo->table->params[DIE] - \
				(philo->table->params[EAT] + philo->table->params[SLP])) >> 1;
	    status_bonus(philo, THNK);
	    my_usl33p(philo, think, get_timestamp());
    }
}
