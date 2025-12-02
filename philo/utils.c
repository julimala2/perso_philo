/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:55:20 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/07 16:24:36 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int  ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
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
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return (result * sign);
}

int return_with_message_and_free(char *str, int exit_code, int free, t_data *data)
{
    printf("%s\n", str);
	if (free == 1)
		ft_free_struct(data);
    return(exit_code);
}

void ft_free_struct(t_data *data)
{
	if (data)
	{
		if (data->forks)
			free(data->forks);
		if (data->threads_id)
			free(data->threads_id);
		if(data->philosophers)
			free(data->philosophers);
	}
}

long	get_time_in_ms()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}