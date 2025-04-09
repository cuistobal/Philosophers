/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sub_routines2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:17:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/09 18:00:52 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool release_forks(t_phil *philosopher, bool even)
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

//yummy yummy, I love spaghettis
static bool	scronch_scronch(t_phil *philosopher, bool even)
{
	long	meal_start;

	if (!the_show_must_go_on(philosopher))
		return (false);
	pthread_mutex_lock(&philosopher->clock);
	philosopher->stats[LMEAL] = get_timestamp();
	meal_start = philosopher->stats[LMEAL];
	philosopher->stats[EATEN]++;
	pthread_mutex_unlock(&philosopher->clock);
	status(philosopher, EATS);
	my_usleep(philosopher, philosopher->table->params[EAT], meal_start);
	return (release_forks(philosopher, even));
}

//Ma forky boiiii
static bool	pick_forks(t_phil *philosopher, bool even)
{
	if (even)
	{
		pthread_mutex_lock(philosopher->lfork);
		if (!the_show_must_go_on(philosopher))
			return (pthread_mutex_unlock(philosopher->lfork), false);
		status(philosopher, FORK);
		pthread_mutex_lock(philosopher->rfork);
		if (!the_show_must_go_on(philosopher))
			return (release_forks(philosopher, even), false);
		status(philosopher, FORK);
	}
	else
	{
		pthread_mutex_lock(philosopher->rfork);
		if (!the_show_must_go_on(philosopher))
			return (pthread_mutex_unlock(philosopher->rfork), false);
		status(philosopher, FORK);
		pthread_mutex_lock(philosopher->lfork);
		if (!the_show_must_go_on(philosopher))
			return (release_forks(philosopher, even), false);
		status(philosopher, FORK);
	}
	return (true);
}

// *scronch scronch scronch*
void	eating(t_phil *philosopher, bool even)
{
	if (the_show_must_go_on(philosopher))
	{
		if (!pick_forks(philosopher, even))
			return ;
		if (the_show_must_go_on(philosopher) && \
				scronch_scronch(philosopher, even))
			return ;
		release_forks(philosopher, even);
	}
}
