/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/17 14:26:58 by cuistobal        ###   ########.fr       */
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
		sem_wait(philo->table->semaphores[MONT]);
		sem_wait(philo->clock);
		if (get_timestamp() - philo->stats[LMEAL] >= die)
		{
            philo->status[0] = true;
            sem_post(philo->clock);
			philo->table->sim = false;
			sem_post(philo->table->semaphores[MONT]);
			sem_post(philo->table->semaphores[DEAD]);
			break ;
		}
		if (meals > 0 && philo->stats[EATEN] >= meals)
		{
            philo->status[1] = true;
            sem_post(philo->clock);
			sem_post(philo->table->semaphores[MONT]);
			sem_post(philo->table->semaphores[FULL]);
			break ;
		}
        sem_post(philo->clock);
		sem_post(philo->table->semaphores[MONT]);
		usleep(TCAP);
	}
	return (NULL);
}

//
static void	routine(t_phil *philo)
{
	pthread_t	death;

    pthread_create(&death, NULL, death_monitor, philo);
	pthread_detach(death);
	while (get_timestamp() < philo->stats[START])
		usleep(1);

	if (philo->stats[POSTN] & 1)
		thinking(philo);

	while (the_sh0w_must_go_on(philo->table))
	{
		eating(philo);
//	    if (philo->status[1])
  //          exit(0);
        sleeping(philo);
		thinking(philo);
	}
    exit(get_timestamp() - philo->stats[LMEAL] <= philo->table->params[DIE]);
}

//
bool	create_child_process(t_phil	*philosopher)
{
	philosopher->pid = fork();
	if (philosopher->pid < 0)
	{
		printf(FORK_ERROR);
		return (false);	
	}
	else if (philosopher->pid == 0)
		routine(philosopher);
	return (true);
}
