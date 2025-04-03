/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/03 13:57:27 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

int		my_atoi(char *argv);

//bool	cleanup(t_tabl *table, ...);
bool	cleanup(t_tabl *table, char *message);

bool	the_show_must_go_on(t_phil *philo);
void	my_usleep(t_phil *philo, long sleep, long start);
long	get_timestamp(void);
void	status(t_phil *philosopher, char *message);
void	*get_value(pthread_mutex_t *mutex, void *value);

bool	you_are_dead(t_phil *philo);

inline static long	my_min(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

#endif
