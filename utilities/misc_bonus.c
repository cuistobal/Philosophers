/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:14:55 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/19 17:08:38 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
bool	the_sh0w_must_go_on(t_tabl *table)
{
	bool	value;

	value = false;
	sem_wait(table->semaphores[MONT]);
    value = table->sim;	
	sem_post(table->semaphores[MONT]);
	return (value);
}

//
void	my_usl33p(t_phil *philo, long sleep, long start)
{
	long	remainder;

	remainder = 0;
	while (the_sh0w_must_go_on(philo->table))
	{
		remainder = sleep - (get_timestamp() - start);
		if (remainder <= 0)
			break ;
		else if (remainder > TCAP / MSEC)
			usleep(TCAP);
		else
			usleep(remainder * MSEC);
	}
}

static void	minitoa(char *message, int *len, int num)
{
	int		index;
	char	temp[INT_SIZE];

	index = 0;
	memset(temp, '\0', sizeof(char) * INT_SIZE);
	while (num >= 0)
	{
		temp[index] = num % 10 + '0';
		if (num == 0 || num / 10 == 0)
		{
			index++;
			break ;
		}
		num = num / 10;
		index++;
	}
	temp[index] = ' ';
	while (--index >= 0)
	{
		message[*len] = temp[index];
		(*len)++;
	}
}

void	status_bonus(t_phil *philo, char *status)
{
	int		len;
	int		index;
	char	message[256];

	len = 0;
	index = 0;
	memset(message, '\0', sizeof(char) * 256);
	minitoa(message + len, &len, get_timestamp() - philo->stats[START]);
	message[len] = ' ';
	len++;	
	minitoa(message, &len, philo->stats[POSTN]);
	message[len] = ' ';
	len++;
	my_strcpy(message + len, status);
	len = len + my_strlen(status);	
	message[len] = '\n';		
	sem_wait(philo->clock);
	write(STDOUT_FILENO, message, len);
	sem_post(philo->clock);
}

//
long	get_timestamp(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * MSEC) + (current.tv_usec / MSEC));
}

