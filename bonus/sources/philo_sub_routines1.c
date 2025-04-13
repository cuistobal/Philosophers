/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sub_routines1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:46:15 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/13 13:10:39 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"


static bool release_forks(t_phil *philosopher)
{
	sem_post(&philosopher->table->semaphores[F0RK]);
	sem_post(&philosopher->table->semaphores[F0RK]);
	return (true);
}

//Ma forky boiiii
static bool	pick_forks(t_phil *philosopher)
{

	sem_wait(&philosopher->table->semaphores[F0RK]);
	if (!the_show_must_go_on(philosopher))
		return (sem_post(&philosopher->table->semaphores[F0RK]), false);	
	status(philosopher, FORK);
	
	//	LONE PHILO
	if (philosopher->table->params[CNT] == 1)
	{
		sem_post(&philosopher->table->semaphores[F0RK]);	
		return (my_usleep(philosopher, philosopher->table->params[DIE], get_timestamp()), false);	
	}
	
	sem_wait(&philosopher->table->semaphores[F0RK]);
	if (!the_show_must_go_on(philosopher))
		return (sem_post(&philosopher->table->semaphores[F0RK]), false);
	status(philosopher, FORK);
	return (true);
}

//yummy yummy, pasta al pastrami
static bool	scronch_scronch(t_phil *philosopher)
{
	long	meal_start;

	sem_wait(&philosopher->clock);
	if (!the_show_must_go_on(philosopher))
		return (sem_post(&philosopher->clock), false);
	philosopher->stats[LMEAL] = get_timestamp();
	meal_start = philosopher->stats[LMEAL];
	philosopher->stats[EATEN]++;
	sem_post(&philosopher->clock);
	status(philosopher, EATS);
	my_usleep(philosopher, philosopher->table->params[EAT], meal_start);
	return (release_forks(philosopher));
}

// *scronch scronch scronch*
void	eating(t_phil *philosopher)
{
	if (the_show_must_go_on(philosopher))
	{
		if (!pick_forks(philosopher))
			return ;
		if (!the_show_must_go_on(philosopher) || \
				!scronch_scronch(philosopher))
			release_forks(philosopher);
	}
}

