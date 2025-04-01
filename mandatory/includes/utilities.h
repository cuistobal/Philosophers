/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 13:26:38 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

int		my_atoi(char *argv);

bool	cleanup(t_tabl *table, ...);

long	get_timestamp(void);

void	status(t_phil *philosopher, char *message);

void	set_value(pthread_mutex_t *mutex, void *value, void *new, size_t size);
void	*access_value(pthread_mutex_t *mutex, void *value);

inline static bool	you_are_dead(t_phil *philo)
{
	long	die;
	long	last_meal;

	pthread_mutex_lock(&philo->clock);
	last_meal = philo->stats[LMEAL];
	die = philo->table->params[DIE];

//	printf("%ld	for	%ld\n", get_timestamp() - last_meal, die);

	pthread_mutex_unlock(&philo->clock);
	return ((get_timestamp() - last_meal) >= die);
}

#endif
