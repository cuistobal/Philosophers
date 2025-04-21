/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/21 11:47:34 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
void	*death_monitor(void *data)
{
	long 	die;
	t_phil	*philo;

	philo = (t_phil *)data;
	die = philo->table->params[DIE];
	while (1)
	{
		sem_wait(philo->clock);
		if (get_timestamp() - philo->stats[LMEAL] >= die)
		{
			sem_post(philo->clock);
			status_bonus(philo, DIED);
			philo->table->sim = false;
			sem_post(philo->table->semaphores[DEAD]);	
			exit(2);
		}
  	    sem_post(philo->clock);
		usleep(MSEC);
	}
	return (NULL);
}

//
int		routine(t_phil *philo)
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
		sem_wait(philo->clock);
		if (philo->table->params[END] > 0 && \
				philo->stats[EATEN] == philo->table->params[END])
			exit(1);
		//	return (cleanup_bonus(&philo->table, NULL) , 1);
				//					sem_post(philo->clock), 1);
		sem_post(philo->clock);
		if (!the_sh0w_must_go_on(philo->table))
			break ;
        eating(philo);
		if (!the_sh0w_must_go_on(philo->table))
			break ;
        sleeping(philo);
        if (!the_sh0w_must_go_on(philo->table))
            break ;
		thinking(philo);
	}
    return (cleanup_bonus(&philo->table, NULL), 2);
}
