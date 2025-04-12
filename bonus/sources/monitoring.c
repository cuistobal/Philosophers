/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:21:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/12 16:45:09 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*monitoring(void *data)
{
	t_tabl	*table;

	table = (t_tabl *)data;
	while (table->simulation)
	{
		if (!waiter(table))
	}
	return (NULL);
}
