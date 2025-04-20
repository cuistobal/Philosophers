/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:07:55 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/20 09:24:44 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

//
typedef struct phil
{
	pid_t			pid;
	pthread_t		death;
	sem_t			*clock;
	struct table	*table;
	long			stats[STATS];
	char			semaname[BUFFER_SIZE];
}	t_phil;

//
typedef struct table
{
	bool		sim;
	struct phil	*philo;
	long		params[TABLES];
	sem_t		*semaphores[SEMP];
}	t_tabl;

#endif
