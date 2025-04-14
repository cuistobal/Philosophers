/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:38:31 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 10:51:26 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_BONUS_H
# define UTILITIES_BONUS_H

# include "utilities.h"

void	unlink_semaphores(void);

void	cleanup_bonus(t_tabl *table, char *message);

//bool	waiter(int count);
bool	waiter(t_tabl *table);

void	sem_name(char *buffer, char *name, int id);
void	itoa(char *buffer, int size, int num);
void	my_strcpy(char *dest, char *from);

#endif
