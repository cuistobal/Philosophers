/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/19 11:31:47 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
void	*death_monitor(void *data)
{
	long 	die;
	long	meals;
	t_phil	*philo;

	philo = (t_phil *)data;
	die = philo->table->params[DIE];
	meals = philo->table->params[END];	
	while (1)
	{
		sem_wait(philo->clock);
		if (get_timestamp() - philo->stats[LMEAL] >= die)
		{
			sem_post(philo->clock);
			status_bonus(philo, DIED);
			philo->table->sim = false;
			sem_post(philo->table->semaphores[DEAD]);
			break ;
		}
		else if (meals > 0)
		{
			if (philo->stats[EATEN] >= meals)
			{
  	      		sem_post(philo->clock);
				sem_post(philo->table->semaphores[DEAD]);
				break ;
			}
  	      	sem_post(philo->clock);
		}
		usleep(TCAP);
	}
	return (NULL);
}

//
void	routine(t_phil *philo)
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
        sleeping(philo);
		thinking(philo);
	}
}
