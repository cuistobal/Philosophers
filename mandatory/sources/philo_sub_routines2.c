/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sub_routines2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:46:15 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/21 15:40:36 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	release_forks(t_phil *philosopher, bool even)
{
	if (even)
	{
		pthread_mutex_unlock(philosopher->lfork);
		pthread_mutex_unlock(philosopher->rfork);
	}
	else
	{
		pthread_mutex_unlock(philosopher->rfork);
		pthread_mutex_unlock(philosopher->lfork);
	}
	return (true);
}

//Ma forky boiiii
static bool	pick_forks_uneven(t_phil *philosopher)
{
	pthread_mutex_lock(philosopher->rfork);
	if (!the_show_must_go_on(philosopher))
		return (pthread_mutex_unlock(philosopher->rfork), false);
	status(philosopher, FORK);
	if (philosopher->table->params[CNT] == 1)
	{
		pthread_mutex_unlock(philosopher->rfork);
		return (my_usleep(philosopher, philosopher->table->params[DIE], \
					get_timestamp()), false);
	}	
	pthread_mutex_lock(philosopher->lfork);
	if (!the_show_must_go_on(philosopher))
		return (release_forks(philosopher, false), false);
	status(philosopher, FORK);
	return (true);
}

//Ma forky boiiii
static bool	pick_forks_even(t_phil *philosopher)
{
	pthread_mutex_lock(philosopher->lfork);
	if (!the_show_must_go_on(philosopher))
		return (pthread_mutex_unlock(philosopher->lfork), false);
	status(philosopher, FORK);
	if (philosopher->table->params[CNT] == 1)
	{
		pthread_mutex_unlock(philosopher->rfork);
		return (my_usleep(philosopher, philosopher->table->params[DIE], \
					get_timestamp()), false);
	}
	pthread_mutex_lock(philosopher->rfork);
	if (!the_show_must_go_on(philosopher))
		return (release_forks(philosopher, true), false);
	status(philosopher, FORK);
	return (true);
}

//yummy yummy, pasta al pastrami
static bool	scronch_scronch(t_phil *philosopher, bool even)
{
	long	meal_start;

	pthread_mutex_lock(&philosopher->clock);
	if (!the_show_must_go_on(philosopher))
		return (pthread_mutex_unlock(&philosopher->clock), false);
	philosopher->stats[LMEAL] = get_timestamp();
	meal_start = philosopher->stats[LMEAL];
	philosopher->stats[EATEN]++;
	pthread_mutex_unlock(&philosopher->clock);
	status(philosopher, EATS);
	my_usleep(philosopher, philosopher->table->params[EAT], meal_start);
	return (release_forks(philosopher, even));
}

// *scronch scronch scronch*
void	eating(t_phil *philosopher, bool even)
{
	if (the_show_must_go_on(philosopher))
	{
		if (even && !pick_forks_even(philosopher))
			return ;
		if (!even && !pick_forks_uneven(philosopher))
			return ;
		if (!the_show_must_go_on(philosopher) || \
				!scronch_scronch(philosopher, even))
			release_forks(philosopher, even);
	}
}
