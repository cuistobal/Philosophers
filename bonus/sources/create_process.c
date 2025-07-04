/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/07/04 10:54:58 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
void	*death_monitor(void *data)
{
	long	die;
	t_phil	*philo;

	philo = (t_phil *)data;
	die = philo->table->params[DIE];
	while (true)
	{
		sem_wait(philo->clock);
		if (get_timestamp() - philo->stats[LMEAL] >= die)
		{
			sem_post(philo->clock);
			// Try to be the first to acquire death message semaphore
			if (sem_trywait(philo->table->semaphores[SEMP - 1]) == 0)
			{
				// We are the first to die, display message and signal others
				status_bonus(philo, DIED);
				sem_wait(philo->table->semaphores[MONT]);
				philo->table->sim = false;
				sem_post(philo->table->semaphores[MONT]);
				sem_post(philo->table->semaphores[DEAD]);
			}
			// In all cases, exit the process
			exit(2);
		}
		sem_post(philo->clock);
		usleep(MSEC);
	}
	return (NULL);
}

static bool	philo_is_full(t_phil *philo)
{
	if (philo->table->params[END] > 0 && \
			philo->stats[EATEN] == philo->table->params[END])
	{
		sem_post(philo->clock);
		philo->table->sim = false;
		return (true);
	}
	return (false);
}

//
int	routine(t_phil *philo)
{
	pthread_t	death;

	while (get_timestamp() < philo->stats[START])
		usleep(1);
	pthread_create(&death, NULL, death_monitor, philo);
	pthread_detach(death);
	if (!(philo->stats[POSTN] & 1))
		thinking(philo);
	while (the_sh0w_must_go_on(philo->table))
	{
		eating(philo);
		sem_wait(philo->clock);
		if (philo_is_full(philo))
			exit(1);
		sem_post(philo->clock);
		if (!the_sh0w_must_go_on(philo->table))
			break ;
		sleeping(philo);
		if (!the_sh0w_must_go_on(philo->table))
			break ;
		thinking(philo);
	}
	exit(2);
}
