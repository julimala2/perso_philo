/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:01:56 by jmalaval          #+#    #+#             */
/*   Updated: 2025/12/16 16:36:56 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE
# define _XOPEN_SOURCE 700
# define _POSIX_C_SOURCE 200809L

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKE_FORK "has taken a fork"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define DIED "died"

#endif

struct s_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				is_dead;
	int				is_eating;
	int				eat_count;
	long			last_eat_time;
	struct s_data	*data;

}					t_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				ate_enough;
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_t		*threads_id;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	check_mutex;
}					t_data;

// init.c
int					init_malloc(t_data *data);
void				init_forks(t_data *data);
void				init_philosophers(t_data *data);

// routine.c
void				manage_forks(t_philo *philo, char c);
void				eat(t_philo *philo);
void				print_action(t_philo *philo, char *message);
void				*routine(void *philo_ptr);

// thread.c
int					init_threads(t_data *data);
void				*monitor(void *data_ptr);
void				*kill_philosophers(t_data *data, int print,
						long current_time, int i);
int					check_if_ate_enough(t_data *data);

// utils.c
int					ft_isdigit(char c);
int					ft_atoi(const char *nptr);
int					return_with_message_and_free(char *str, int exit_code,
						int free, t_data *data);
long				get_time_in_ms(void);
void				ft_free_struct(t_data *data);

// main.c
int					set_parameters(char **av, t_data *data);
int					check_digit_args(char **av);