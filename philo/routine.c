/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:56:35 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/07 17:35:14 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    manage_forks(t_philo *philo, char c)
{
    if (c == 's')
    {
        pthread_mutex_lock(philo->r_fork);
        print_action(philo, TAKE_FORK);
        pthread_mutex_lock(philo->l_fork);
        print_action(philo, TAKE_FORK);
    }
    else if (c == 'e')
    {
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        print_action(philo, SLEEP);
        usleep(philo->data->time_to_sleep);
    }
}

void eat(t_philo *philo)
{
    manage_forks(philo, 's');
    pthread_mutex_lock(philo->data->forks);
    philo->is_eating = 1;
    philo->last_eat_time = get_time_in_ms();
    print_action(philo, EAT);
    usleep(philo->data->time_to_eat);
    philo->is_eating = 0;
    philo->eat_count++;
    pthread_mutex_unlock(philo->data->forks);
    manage_forks(philo, 'e');
}

void    print_action(t_philo *philo, char *message)
{
    long time;

    if (philo)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        time = get_time_in_ms() - philo->data->start_time;
        printf("%ld %d %s\n", time, philo->id, message);
        pthread_mutex_unlock(&philo->data->print_mutex);
    }
}

void    *routine(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *)philo_ptr;
    philo->last_eat_time = get_time_in_ms();
    while (!philo->is_dead)
    {
        eat(philo);
        print_action(philo, THINK);
    }
    return (NULL);
}