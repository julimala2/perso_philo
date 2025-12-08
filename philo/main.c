/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:46:35 by jmalaval          #+#    #+#             */
/*   Updated: 2025/12/08 17:25:21 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Your program(s) must take the following arguments: 
//number_of_philosophers 
//time_to_die 
//time_to_eat 
//time_to_sleep 
//[number_of_times_each_philosopher_must_eat]

int main(int ac, char **av)
{
    t_data *data;

    if (ac < 5 || ac > 6)
        return(1);
    data = malloc(sizeof(t_data));
    if (!data)
        return(1);
    if (set_parameters(av, data) == 1)
    {
        ft_free_struct(data);
        return(1);
    }
    if (init_malloc(data))
        return_with_message_and_free(NULL, 1, 1, data);
    init_forks(data);
    init_philosophers(data);
    init_threads(data);
    ft_free_struct(data);
    return(0);
}

int    set_parameters(char **av, t_data *data)
{
    if (check_digit_args(av) == 1)
        return(1);
    data->number_of_philosophers = ft_atoi(av[1]);
    if (data->number_of_philosophers < 1)
        return_with_message_and_free("Incorrect number of philosophers\n", 1, 1, data);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    data->start_time = get_time_in_ms();
    if (data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
        return_with_message_and_free("Time must be > 0\n", 1, 1, data);
    if (av[5])
        data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
    else
        data->number_of_times_each_philosopher_must_eat = -1;
    return(0);
}

int check_digit_args(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (!ft_isdigit(av[i][j]))
            {
                printf("Argument Error\n");
                return(1);
            }
            j++;
        }
        i++;
    }
    return(0);
}
