/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/01 13:58:49 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

//initialisation.c
bool	init_table(t_tabl **table, char **argv);

//monitoring.c
void	*alive_and_not_full(void *data);
bool	the_show_must_go_on(t_phil *philosopher);

//routines.c
void	*routine(void *arg);

//sub_routines.c
void	eating(t_phil *philosopher);
void	sleeping(t_phil *philosopher);
void	thinking(t_phil *philosopher);

#endif
