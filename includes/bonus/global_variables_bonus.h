/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variables_bonus.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:42:18 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 12:13:51 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_VARIABLES_BONUS_H
# define GLOBAL_VARIABLES_BONUS_H

# include "global_variables.h"

//Semaphor's names
# define FORKS "/fork_sem"
# define MONIT "/monitoring_sem"
# define BEGIN "/begin_sem"
# define CLOCK "/clock_sem"

# define SFORKS "sem.fork_sem"
# define SMONIT "sem.monitoring_sem"
# define SBEGIN "sem.begin_sem"
# define SCLOCK "sem.clock_sem"

//Sempahores attributes -Used only in sem_init()-
# define LOCAL 0
# define SHARED 1

//Types of semaphors
# define SEMP 3

# define F0RK 0
# define MONT 1
# define BEGN 2


//Philo's return values
# define SUCES 0 
# define FULL 1
# define DEATH 2
# define MEM 3 

//Utilities
# define BUFFER_SIZE 256
# define INT_SIZE 12

//Errors
# define FORK_ERROR "Call to fork() failed.\n"
# define F0RK_ERROR -1

#endif
