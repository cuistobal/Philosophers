/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:25:32 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/03 14:25:53 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//The philos are right handed if an even number sits around the table. They
//become left handed otherwise.
void	thinking(t_phil	*philosopher)
{
	if (the_show_must_go_on(philosopher))
	{
		pthread_mutex_lock(&philosopher->clock);
		pthread_mutex_unlock(&philosopher->clock);
		status(philosopher, THNK);
		my_usleep(philosopher, 1, get_timestamp());
	}
}
