/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:56:35 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/12/11 16:15:39 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    manage_forks(t_philo *philo, char c)
{
    if (c == 's')
    {
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->l_fork);
            print_action(philo, TAKE_FORK);
            pthread_mutex_lock(philo->r_fork);
            print_action(philo, TAKE_FORK);
        }
        else
        {
            pthread_mutex_lock(philo->r_fork);
            print_action(philo, TAKE_FORK);
            pthread_mutex_lock(philo->l_fork);
            print_action(philo, TAKE_FORK);
        }
    }
    else if (c == 'e')
    {
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        print_action(philo, SLEEP);
        usleep(philo->data->time_to_sleep * 1000);
    }
}

void eat(t_philo *philo)
{
    manage_forks(philo, 's');
    pthread_mutex_lock(&philo->data->check_mutex);
    philo->is_eating = 1;
    philo->last_eat_time = get_time_in_ms();
    pthread_mutex_unlock(&philo->data->check_mutex);
    print_action(philo, EAT);
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_lock(&philo->data->check_mutex);
    philo->is_eating = 0;
    philo->eat_count++;
    pthread_mutex_unlock(&philo->data->check_mutex);
    manage_forks(philo, 'e');
}

void    print_action(t_philo *philo, char *message)
{
    long time;

    pthread_mutex_lock(&philo->data->check_mutex);
    if (philo && !philo->is_dead)
    {
        time = get_time_in_ms() - philo->data->start_time;
        pthread_mutex_unlock(&philo->data->check_mutex);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d %s\n", time, philo->id, message);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
    else
        pthread_mutex_unlock(&philo->data->check_mutex);
}

void    *routine(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *)philo_ptr;
    if (philo->data->number_of_philosophers == 1)
    {
        pthread_mutex_lock(philo->r_fork);
        print_action(philo, TAKE_FORK);
        usleep(philo->data->time_to_die * 1000);
        pthread_mutex_unlock(philo->r_fork);
        return (NULL);
    }
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!philo->is_dead)
    {
        eat(philo);
        print_action(philo, THINK);
        usleep(1000);
    }
    return (NULL);
}
