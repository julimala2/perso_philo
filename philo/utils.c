/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:55:20 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/03 15:05:38 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_sign(char c)
{
	if (c == '-')
		return(-1);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 7 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = ft_sign(nptr[i]);
		i++;
	}
	if (!(ft_isdigit(nptr[i])))
		return (0);
	else
	{
		while (nptr[i] && ft_isdigit(nptr[i]))
		{
			result = result * 10 + (nptr[i] - 48);
			i++;
		}
		return (result * sign);
	}
}

void exit_with_message(char *str, int exit_code)
{
    printf("%s\n", str);
    exit(exit_code);
}