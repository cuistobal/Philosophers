/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/13 17:03:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//

void	my_usleep(t_phil *philo, long sleep, long start)
{
	long	remainder;

	remainder = sleep - (get_timestamp() - start);
	if (remainder <= 0)
		return ;
	else
	{
		if (remainder > TCAP / MSEC)
			usleep(TCAP);
		else
			usleep(remainder * MSEC);
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
	printf("%ld %ld %s", get_timestamp() - philo->stats[START], \
			philo->stats[POSTN], status);
	pthread_mutex_unlock(&philo->table->write);
}

//
long	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * MSEC) + (current.tv_usec / MSEC));
}
