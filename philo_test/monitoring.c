/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:16:29 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/19 14:33:04 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(t_data *data)
{
	data->start_time = get_time();
	while (1)
	{
		if (death_monitoring(data) == 1)
			break ;
		if (eat_monitoring(data) == 1)
			break ;
	}
	return (NULL);
}

int	death_monitoring(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (death_check(&data->philos[i]) == 1)
		{
			print_message("died", data, data->philos[i].id);
			pthread_mutex_lock(&data->death_mutex);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
	}
	return (0);
}

int	eat_monitoring(t_data *data)
{
	int	i;
	int	finished_count;

	i = -1;
	finished_count = 0;
	if (data->must_eat_count == -1)
		return (0);
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].eat_mutex);
		if (data->philos[i].eat_count >= data->must_eat_count)
			finished_count++;
		pthread_mutex_unlock(&data->philos[i].eat_mutex);
	}
	if (finished_count == data->philo_count)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}
