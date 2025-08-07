/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:22:10 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/07 15:23:13 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	if (data->philo_dead)
		return (1);
	pthread_mutex_lock(&data->ready_mutex);
	while (i < data->args[0])
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				(void *)philo_routine, &data->philos[i]))
			break ;
		data->philo_count = ++i;
	}
	data->start_time = get_time();
	pthread_mutex_unlock(&data->ready_mutex);
	if (pthread_create(&monitor_thread, NULL, (void *)monitoring, data))
		return (1);
	if (pthread_join(monitor_thread, NULL))
		return (1);
	i = -1;
	while (++i < data->args[0])
		if (pthread_join(data->philos[i].thread, NULL))
			break ;
	return (0);
}
