/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 13:55:57 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct table
{
	pthread_t		thread;
	pthread_mutex_t	*fork;
	struct philo	*philo;
	pthread_mutex_t	monitoring;
	long			params[TABLES];
}	t_tabl;

typedef struct philo
{
	pthread_t		thread;
	pthread_mutex_t	clock;
	pthread_mutex_t	write;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	struct table	*table;
	long			stats[STATS];
}	t_phil;

#endif
