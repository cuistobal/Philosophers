/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/03 14:41:09 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

//initialisation.c
bool	init_table(t_tabl **table, char **argv);

//monitoring_routine.c
bool	you_are_dead(t_phil *philo);
bool	you_are_full(t_tabl *table, t_phil *philo);
void	*monitoring(void *data);

//philo_routine.c
void	*routine(void *arg);

//philo_sub_routines.c
void	eating(t_phil *philosopher, bool even);
void	sleeping(t_phil *philosopher);
void	thinking(t_phil *philosopher);

#endif
