/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:46:35 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/03 19:11:00 by jmalaval         ###   ########.fr       */
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
    t_param *arguments;

    if (ac < 5 || ac > 6)
        return(1);
    arguments = malloc(sizeof(t_param));
    if (!arguments)
        return(1);
    if (set_parameters(av, arguments) == 1)
        return(1);
    return(0);
    // créer les numbers philosophers 
    // créer une routine : prendre une fourchette, manger, poser la fourchette, dormir, penser
}

int    set_parameters(char **av, t_param *param)
{
    
    param->number_of_philosophers = ft_atoi(av[1]);
    if (param->number_of_philosophers < 1)
        exit_with_message("Incorrect number of philosophers\n", 1);
    param->time_to_die = ft_atoi(av[2]);
    //cas d'erreur ? 
    param->time_to_eat = ft_atoi(av[3]);
    //erreur
    param->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
    {
        param->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
        //cas d'erreur
    }
    return(0);
}
