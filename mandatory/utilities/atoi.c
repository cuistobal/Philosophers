/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:07:20 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/29 12:07:23 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//
static bool	is_sign(char **argv, int *sign)
{
	if (**argv == '-' || **argv == '+')
	{
		if (**argv == '-')
			*sign = *sign * -1;
		(*argv)++;
		return (true);
	}
	return (false);
}

//
static void	skip_spaces_get_sign(char **argv, int *sign)
{
	while (*argv)
	{
		if (isspace(**argv))
			(*argv)++;
		else if (!is_sign(argv, sign))
			break ;
	}
}

//
int	my_atoi(char *argv)
{
	int	ans;
	int	sign;

	ans = 0;
	sign = 1;
	if (argv)
	{
		skip_spaces_get_sign(&argv, &sign);
		while (*argv)
		{
			if (!isdigit(*argv))
				break ;
			ans = (ans * 10) + (*argv - '0');
			argv++;
		}
	}
	return (ans * sign);
}
