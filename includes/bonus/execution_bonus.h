/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:12:37 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/21 15:13:26 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_BONUS_H
# define EXECUTION_BONUS_H

int		routine(t_phil *philo);

bool	init_table(t_tabl **table, char **argv);

bool	create_child_process(t_phil *philo);

void	eating(t_phil *philosopher);
void	sleeping(t_phil *philosopher);
void	thinking(t_phil *philosopher);

#endif
