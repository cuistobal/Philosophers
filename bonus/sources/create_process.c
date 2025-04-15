/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/15 15:43:51 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
			break ;
		
		/*
		else if (meals > 0 && philo->stats[EATEN] == meals)
			break ;
		*/
		
		sem_post(philo->clock);
		usleep(TCAP);
	}
	return (NULL);
}

static void	routine(t_phil *philo)
{
	pthread_t	death;
	int			exit_code;

	exit_code = 0;
	
	pthread_create(&death, NULL, death_monitor, philo);
	pthread_detach(death);

	int value;
	
	sem_getvalue(philo->table->semaphores[BEGN], &value);
	printf("sem's value -> %d", value);
	
	sem_wait(philo->table->semaphores[BEGN]);

	philo->stats[LMEAL] = philo->table->params[STS];

	sem_post(philo->table->semaphores[BEGN]);
	if (philo->stats[POSTN] & 0)
		thinking(philo);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	pthread_join(death, NULL);
	exit(exit_code);
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
	printf("process %d\n", philosopher->pid);
	return (true);
}
