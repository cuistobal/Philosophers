/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 12:04:58 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
void	set_value(pthread_mutex_t *mutex, void *current, void *new, size_t size)
{
	pthread_mutex_lock(mutex);
	memcpy(current, new, size);
	pthread_mutex_unlock(mutex);
}

//This function allows us to access value thread safely
void	*access_value(pthread_mutex_t *mutex, void *value)
{
	void	*accessed;

	pthread_mutex_lock(mutex);
	accessed = value;
	pthread_mutex_unlock(mutex);
	return (accessed);
}

//
void	status(t_phil *philo, char *status)
{
	long	time;
	long	position;

	pthread_mutex_lock(&philo->write);
	time = philo->stats[START];
	position = philo->stats[POSTN];
	printf("%ld %ld %s", get_timestamp() - time, position, status);
	pthread_mutex_unlock(&philo->write);
}

//
long	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_usec / MSEC);
}
