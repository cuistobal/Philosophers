/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:08:49 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/09 17:10:34 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

typedef struct table
{
	pthread_t		thread;
	sem_t			*fork;
	struct philo	*philo;
	sem_t			write;
	sem_t			monitoring;
	bool			simulation;
	long			params[TABLES];
}	t_tabl;

typedef struct philo
{
	pthread_t		thread;
	sem_t			clock;
	sem_t			*lfork;
	sem_t			*rfork;
	struct table	*table;
	long			stats[STATS];
}	t_phil;

#endif
