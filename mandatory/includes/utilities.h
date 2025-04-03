/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/03 08:58:23 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

int		my_atoi(char *argv);

bool	cleanup(t_tabl *table, ...);

long	get_timestamp(void);

void	status(t_phil *philosopher, char *message);

void	set_value(pthread_mutex_t *mutex, void *value, void *new, size_t size);
void	*get_value(pthread_mutex_t *mutex, void *value);

bool	you_are_dead(t_phil *philo);

inline static long	my_min(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

#endif
