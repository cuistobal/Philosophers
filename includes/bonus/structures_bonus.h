/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:07:55 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 16:08:40 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

//
typedef struct phil
{
	pid_t			*pid;
	sem_t			clock;
	struct table	*table;
	long			stats[STATS];
}	t_phil;

//
typedef struct table
{
	pid_t		*pids;
	struct phil	*philo;
	sem_t		*semaphors;
	p_thread	monitoring;
	long		params[TABLES];
}	t_tabl;

#endif
