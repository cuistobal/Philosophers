/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:14:55 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/17 11:25:01 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
bool	the_sh0w_must_go_on(t_tabl *table)
{
	bool	value;

	value = false;
	sem_wait(table->semaphores[MONT]);
    value = table->sim;	
	sem_post(table->semaphores[MONT]);
	return (value);
}

//
void	my_usl33p(t_phil *philo, long sleep, long start)
{
	long	remainder;

	remainder = 0;
	while (the_sh0w_must_go_on(philo->table))
	{
		remainder = sleep - (get_timestamp() - start);
		if (remainder <= 0)
			break ;
		if (remainder > TCAP / MSEC)
			usleep(TCAP);
		else
			usleep(remainder * MSEC);
	}
}

//
void	status_bonus(t_phil *philo, char *status)
{
	sem_wait(philo->clock);
	printf("%ld %ld %s", get_timestamp() - philo->stats[START], \
			philo->stats[POSTN], status);
	sem_post(philo->clock);
}

//
long	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * MSEC) + (current.tv_usec / MSEC));
}

