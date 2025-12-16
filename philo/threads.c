/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:07:56 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/12/11 15:46:44 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void *monitor(void *data_ptr)
{
    t_data *data;
    int i;
    long current_time;
    int j;
    int ate_enough;

    data = (t_data *)data_ptr;
    while (1)
    {
        i = 0;
        ate_enough = 1;
        while (i < data->number_of_philosophers)
        {
            pthread_mutex_lock(&data->check_mutex);
            current_time = get_time_in_ms();
            if (!data->philosophers[i].is_eating && (current_time - data->philosophers[i].last_eat_time) > data->time_to_die)
            {
                j = 0;
                while (j < data->number_of_philosophers)
                    data->philosophers[j++].is_dead = 1;
                pthread_mutex_unlock(&data->check_mutex);
                pthread_mutex_lock(&data->print_mutex);
                printf("%ld %d %s\n", current_time - data->start_time, data->philosophers[i].id, DIED);
                pthread_mutex_unlock(&data->print_mutex);
                return(NULL);
            }
            else if (data->number_of_times_each_philosopher_must_eat != -1 && data->philosophers[i].eat_count < data->number_of_times_each_philosopher_must_eat)
                ate_enough = 0;
            pthread_mutex_unlock(&data->check_mutex);
            i++;
        }
        if (ate_enough && data->number_of_times_each_philosopher_must_eat != -1)
        {
            pthread_mutex_lock(&data->check_mutex);
            j = 0;
            while (j < data->number_of_philosophers)
                data->philosophers[j++].is_dead = 1;
            pthread_mutex_unlock(&data->check_mutex);
            return(NULL);
        }
    }
    return(NULL);
}

int init_threads(t_data *data)
{
    int i;
    pthread_t   monitor_thread; 

    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_create(&data->threads_id[i], NULL, &routine, &data->philosophers[i]))
            return(return_with_message_and_free("Error creating threads\n", 1, 1, data));
        i++;
    }
    pthread_create(&monitor_thread, NULL, &monitor, data);
    i = 0;
    while (i < data->number_of_philosophers)
    {
        if (pthread_join(data->threads_id[i], NULL))
            return(return_with_message_and_free("Error joining threads\n", 1, 1, data));
        i++;
    }
    pthread_join(monitor_thread, NULL);
    return (0);
}
