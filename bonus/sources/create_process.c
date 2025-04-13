/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:45:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/13 12:17:48 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
static void	routine(t_phil *philo)
{
	bool sim = true;
	long	start = get_timestamp();

	while (sim)
	{
		sim = (get_timestamp() - start) < TCAP;
		if (philo->stats[POSTN] & 1)
		{
//			eating();
//			sleeping();
//			thinking();
			usleep(1000);
			printf("%ld	->	%ld yumyum\n", get_timestamp() - start, philo->stats[POSTN]);
		}
		else
		{
			printf("%ld	->	%ld scrouunchscrounch\n", get_timestamp() - start, philo->stats[POSTN]);
			usleep(100);
//			eating();
//			sleeping();
//			thinking();
		}
	}
}

//
bool	create_child_process(t_tabl *table, int index)
//	t_phil *philo, pid_t *pids)
{
	pid_t	current;
	t_phil	*philosopher;

	philosopher = &table->philo[index];
	current	= fork();
	if (current < 0)
	{
		printf(FORK_ERROR);
		return (false);
		//		exit(F0RK_ERROR);
	}
	else if (current > 0)
	{
		printf("current pid	->	%d\n", current);	
		table->pids[index] = current;
	}
	//	*pids = current;
	else
	//	routine(philo);
		routine(philosopher);
	return true;
}
