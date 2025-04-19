/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:38:31 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/19 09:29:10 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_BONUS_H
# define UTILITIES_BONUS_H

void	status_bonus(t_phil *philo, char *status);

void	my_usl33p(t_phil *philo, long sleep, long start);

int		my_atoi(char *argv);

long	get_timestamp(void);

bool	the_sh0w_must_go_on(t_tabl *table);

void	unlink_semaphores(void);

void	cleanup_bonus(t_tabl *table, char *message);

bool	waiter(t_tabl *table);

void	sem_name(char *buffer, char *name, int id);
void	itoa(char *buffer, int size, int num);
void	my_strcpy(char *dest, char *from);

#endif
