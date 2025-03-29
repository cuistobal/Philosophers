/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/29 12:07:23 by chrleroy         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->table->monitoring);
	time = philo->table->params[STS];
	position = philo->stats[POSTN];
	pthread_mutex_unlock(&philo->table->monitoring);
	printf("%ld %ld %s", get_timestamp() - time, position, status);
}

//
long	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_usec);
}
