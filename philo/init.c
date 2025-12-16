/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:47:18 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/12/11 15:35:59 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_malloc(t_data *data)
{
    data->threads_id = malloc(data->number_of_philosophers * sizeof(pthread_t));
    if (!data->threads_id)
        return_with_message_and_free(NULL, 1, 1, data);
    data->philosophers = malloc(data->number_of_philosophers * sizeof(t_philo));
    if (!data->philosophers)
        return_with_message_and_free(NULL, 1, 1, data);
    data->forks = malloc(data->number_of_philosophers * sizeof(pthread_mutex_t));
    if (!data->forks)
        return_with_message_and_free(NULL, 1, 1, data);
    return(0);
}

void init_forks(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
        pthread_mutex_init(&data->forks[i++], NULL);
    i = 0;
    while (i < data->number_of_philosophers)
    {
        data->philosophers[i].l_fork = &data->forks[i];
        data->philosophers[i].r_fork = &data->forks[(i + 1) % data->number_of_philosophers];
        i++;
    }
}

void    init_philosophers(t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->check_mutex, NULL);
    while (i < data->number_of_philosophers)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].is_eating = 0;
        data->philosophers[i].is_dead = 0;
        data->philosophers[i].data = data;
        data->philosophers[i].last_eat_time = data->start_time;
        data->philosophers[i].eat_count = 0;
        i++;
    }
}

