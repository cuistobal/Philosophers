/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:38:31 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 15:40:03 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_BONUS_H
# define UTILITIES_BONUS_H

bool	waiter(pid_t *pids, int count);

void	sem_name(char *buffer, char *name, int id);
void	itoa(char *buffer, int size, int num);
void	my_strcpy(char *dest, char *from);

#endif
