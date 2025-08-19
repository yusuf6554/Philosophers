/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:08:05 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/19 14:31:56 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	start(t_data *data)
{
	int	i;

	data->threads = malloc(sizeof(pthread_t) * data->philo_count);
	if (!data->threads)
		return (-1);
	i = -1;
	pthread_mutex_lock(&data->sim_mutex);
	while (++i < data->philo_count)
	{
		if (pthread_create(&data->threads[i], NULL, (void *)simulation,
				&data->philos[i]))
			return (-1);
		data->thread_count++;
	}
	if (pthread_create(&data->monitor_thread, NULL, (void *)monitoring, data))
		return (-1);
	pthread_mutex_unlock(&data->sim_mutex);
	if (pthread_join(data->monitor_thread, NULL))
		return (-1);
	i = -1;
	while (++i < data->thread_count)
		if (pthread_join(data->threads[i], NULL))
			return (-1);
	return (1);
}
