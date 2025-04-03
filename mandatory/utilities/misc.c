/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/03 14:14:54 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
bool	the_show_must_go_on(t_phil *philo)
{
	bool	status;

	pthread_mutex_lock(&philo->table->monitoring);
	status = philo->table->simulation;
	pthread_mutex_unlock(&philo->table->monitoring);
	return (status);
}

//
void	my_usleep(t_phil *philo, long sleep, long start)
{
	long	remainder;

	remainder = 0;
	while (the_show_must_go_on(philo))
	{
		remainder = sleep - (get_timestamp() - start);
		if (remainder <= 0)
			break ;
		else 
		{
			if (remainder > TCAP / MSEC)
				usleep(TCAP);
			else
				usleep(remainder * MSEC);
		}
	}
}

//
void	*get_value(pthread_mutex_t *mutex, void *source)
{
	void	*value;

	pthread_mutex_lock(mutex);
	value = source;
	pthread_mutex_unlock(mutex);
	return (value);
}

//
void	status(t_phil *philo, char *status)
{
	pthread_mutex_lock(&philo->table->write);	
	printf("%ld %ld %s", get_timestamp() - philo->stats[START], philo->stats[POSTN], status);
	pthread_mutex_unlock(&philo->table->write);
}

//
long	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * MSEC) + (current.tv_usec / MSEC));
}
