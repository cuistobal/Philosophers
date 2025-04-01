/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 13:15:03 by chrleroy         ###   ########.fr       */
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

//	printf("%ld	->	%ld\n", sleep_time, sleep_time * MSEC);

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

//	printf("Old Timer = %ld	", philosopher->stats[LMEAL]);

	philosopher->stats[LMEAL] = get_timestamp();

//	printf("	->	New Timer = %ld\n", philosopher->stats[LMEAL]);
	
	philosopher->stats[EATEN]++;
	pthread_mutex_unlock(&philosopher->clock);
	status(philosopher, EATS);
	usleep(meal_time * MSEC);
	
//	printf("%ld	->	%ld\n",	meal_time, meal_time * MSEC);
	
	pthread_mutex_unlock(philosopher->lfork);
	pthread_mutex_unlock(philosopher->rfork);
}

//The philos are right handed if an even number sits around the table. They 
//become left handed otherwise.
void	thinking(t_phil	*philosopher)
{	
	status(philosopher, THNK);
//	usleep(100 * MSEC);
}
