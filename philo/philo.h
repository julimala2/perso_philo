/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:01:56 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/07 17:36:13 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE 700
#define _POSIX_C_SOURCE 200809L


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

# define TAKE_FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIED "died" 

#endif

struct s_data;

typedef struct s_philo
{
    int id;
    pthread_t   thread;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    int is_dead;
    int is_eating;
    int eat_count;
    long    last_eat_time;
    struct s_data *data;
    
}   t_philo;

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    long    start_time;
    t_philo *philosophers;
    pthread_mutex_t *forks;
    pthread_t *threads_id;
    pthread_mutex_t print_mutex;
} t_data;


//init.c
int init_malloc(t_data *data);
void init_forks(t_data *data);
void    init_philosophers(t_data *data);

// routine.c
void    manage_forks(t_philo *philo, char c);
void eat(t_philo *philo);
void    print_action(t_philo *philo, char *message);
void    *routine(void *philo_ptr);

//thread.c
int init_threads(t_data *data);
void *monitor(void *data_ptr);

// utils.c
int  ft_isdigit(char c);
int	ft_atoi(const char *nptr);
int return_with_message_and_free(char *str, int exit_code, int free, t_data *data);
long	get_time_in_ms();
void ft_free_struct(t_data *data);

//main.c
int    set_parameters(char **av, t_data *data);
int check_digit_args(char **av);