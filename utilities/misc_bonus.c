/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:14:55 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 10:19:13 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
void	my_usleep(t_phil *philo, long sleep, long start)
{
	long	remainder;

	printf("%ld\n", philo->stats[POSTN]);
	remainder = sleep - (get_timestamp() - start);
	if (remainder > TCAP / MSEC)
		usleep(TCAP);
	else
		usleep(remainder * MSEC);
}

//
void	status(t_phil *philo, char *status)
{
	printf("%ld %ld %s", get_timestamp() - philo->stats[START], \
			philo->stats[POSTN], status);
}

//
long	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * MSEC) + (current.tv_usec / MSEC));
}

