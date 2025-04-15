/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:21:24 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/15 11:34:09 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*kindergarten(void *data)
{
	int		index;
	t_tabl	*table;

	index = 0;
	table = (t_tabl *)data;
	while (table->sim)
	{	
		waiter(table);
	}
	return (NULL);
}
