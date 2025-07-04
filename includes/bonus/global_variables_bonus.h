/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variables_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:42:18 by chrleroy          #+#    #+#             */
/*   Updated: 2025/07/04 10:53:59 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_VARIABLES_BONUS_H
# define GLOBAL_VARIABLES_BONUS_H

# include "global_variables.h"

//Semaphor's names
# define FORKS "/fork_sem"
# define MONIT "/monitoring_sem"
# define CLOCK "/clock_sem"
# define DEATH "/death_sem"
# define BEGIN "/begin_sem"
# define REPUS "/full_sem"
# define DEDMS "/death_msg_sem"

//Sempahores attributes -Used only in sem_init()-
# define LOCAL 0
# define SHARED 1

//Types of semaphors
# define SEMP 4

# define F0RK 0
# define MONT 1
# define DEAD 2
# define BEGN 3
# define FULL 4
# define DEDM 5

//Utilities
# define BUFFER_SIZE 256
# define INT_SIZE 12

//Errors
# define FORK_ERROR "Call to fork() failed.\n"
# define F0RK_ERROR -1

#endif
