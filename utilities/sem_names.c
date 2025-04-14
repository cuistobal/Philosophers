/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_names.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:17:43 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/14 09:46:20 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//
void	itoa(char *buffer, int size, int num)
{
	int		copy;
	int		index;
	char	temp[INT_SIZE];

	copy = 0;
	index = 0;
	while (index < size && index < 11 && num > 0)
	{
		temp[index] =	num % 10 + '0';
		num = num / 10;
		index++;	
	}
	temp[index] = '\0';
	buffer[index] = '\0';
	while (--index >= 0)
	{
		buffer[copy] = temp[index];
		copy++;
	}
}

//
void	my_strcpy(char *dest, char *from)
{
	int	index = 0;

	index = 0;
	while (from[index])
	{
		dest[index] = from[index];
		index++;
	}
}

//
int	my_strlen(char *string)
{
	int	len;

	len = 0;
	while (string[len])
		len++;
	return (len);
}

//
void	sem_name(char *buffer, char *name, int id)
{
	int		index;
	char	identifier[INT_SIZE];
	
	index = strlen(name);
	my_strcpy(buffer, name);
	itoa(identifier, INT_SIZE, id);
	my_strcpy(buffer + index, identifier);
}

/*
int main(int argc, char **argv)
{
	int num = 0;
	char *name;
	char buffer[SIZE] = {0};

	if (argc == 3)
	{
		name = argv[1];
		num = atoi(argv[2]);
		strcpy(buffer, name);
		itoa(buffer + strlen(name), SIZE - strlen(name), num);	
		printf("BUFFER	->	%s\n", buffer);	
	}
	return 0;
}
*/
