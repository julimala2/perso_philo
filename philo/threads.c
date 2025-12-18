/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:07:56 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/12/18 13:20:31 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *data_ptr)
{
	t_data	*data;
	int		i;
	long	current_time;

	data = (t_data *)data_ptr;
	while (1)
	{
		i = -1;
		data->ate_enough = 1;
		while (++i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->check_mutex);
			current_time = get_time_in_ms();
			if (!data->philosophers[i].is_eating && (current_time
					- data->philosophers[i].last_eat_time) > data->time_to_die)
				return (kill_philosophers(data, 1, current_time, i));
			if (data->must_eat_count != -1
				&& data->philosophers[i].eat_count < data->must_eat_count)
				data->ate_enough = 0;
			pthread_mutex_unlock(&data->check_mutex);
		}
		if (data->ate_enough && data->must_eat_count != -1)
			return (kill_philosophers(data, 0, 0, 0));
	}
	return (NULL);
}

void	*kill_philosophers(t_data *data, int print, long current_time, int i)
{
	int	j;

	j = 0;
	if (print == 0)
		pthread_mutex_lock(&data->check_mutex);
	while (j < data->number_of_philosophers)
		data->philosophers[j++].is_dead = 1;
	pthread_mutex_unlock(&data->check_mutex);
	if (print == 1)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d %s\n", current_time - data->start_time,
			data->philosophers[i].id, DIED);
		pthread_mutex_unlock(&data->print_mutex);
	}
	else if (print == 0)
		pthread_mutex_unlock(&data->check_mutex);
	return (NULL);
}

int	init_threads(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&data->threads_id[i], NULL, &routine,
				&data->philosophers[i]))
			return (return_with_message_and_free("Error creating threads\n", 1,
					1, data));
		i++;
	}
	pthread_create(&monitor_thread, NULL, &monitor, data);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->threads_id[i], NULL))
			return (return_with_message_and_free("Error joining threads\n", 1,
					1, data));
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}
