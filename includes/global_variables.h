/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 09:33:12 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_VARIABLES_H
# define GLOBAL_VARIABLES_H

//Table macros
# define TABLES 6

# define STS 0
# define CNT 1
# define DIE 2
# define EAT 3
# define SLP 4
# define END 5

//Philo macros
# define STATS 4

# define POSTN 0
# define LMEAL 1
# define EATEN 2
# define START 3

//Routine messages
# define THNK "is thinking\n"
# define FORK "has taken a fork\n"
# define EATS "is eating\n"
# define SLEP "is sleeping\n"
# define DIED "died\n"

//Error messages
# define ARGC "Usage: ./philosophers philos die eat sleep [min eat]."
# define ATOI "Invalid parameter."
# define THREAD_CREATE "Failed to create Thread."
# define INIT_TABLE "Failed to initialise the simulation."

//Misc
# define SUCCESS "Greaaaaat suucceeeeeees."
# define MSEC 1000
# define TCAP 10000

#endif
