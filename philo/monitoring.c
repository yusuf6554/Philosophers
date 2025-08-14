/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:50:14 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/14 10:45:40 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->start_time = get_time();
	set_status(data, 1);
	while (1)
	{
		if (monitor_deaths(data))
			break ;
		if (monitor_eat_count(data))
			break ;
	}
	return (NULL);
}

int	monitor_deaths(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args[0])
	{
		if (check_dead(&data->philos[i], data->args[1]))
		{
			print_message(&data->philos[i], "died", data->philos[i].id);
			pthread_mutex_lock(&data->dead_mutex);
			data->philo_dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitor_eat_count(t_data *data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (data->args[4] == -1)
		return (0);
	while (++i < data->args[0])
	{
		pthread_mutex_lock(&data->philos[i].eat_mutex);
		if (data->philos[i].eat_count >= data->args[4])
			count++;
		pthread_mutex_unlock(&data->philos[i].eat_mutex);
	}
	if (count == data->args[0])
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->philo_dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	return (0);
}
