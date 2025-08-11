/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:58:36 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/11 14:22:58 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

static void	free_philos(t_philo *philos);

int	handle_error(t_data *data, int error_code, char *message)
{
	int	index;

	index = -1;
	if (error_code == 0)
	{
		data->philo_dead = 1;
		if (data->mutex_error > 0)
			pthread_mutex_destroy(&data->dead_mutex);
		if (data->mutex_error > 1)
			pthread_mutex_destroy(&data->print_mutex);
		if (data->mutex_error > 2)
			pthread_mutex_destroy(&data->ready_mutex);
		while (++index < data->args[0])
			if (data->forks)
				pthread_mutex_destroy(&data->forks[index]);
		if (data->philos)
			free_philos(data->philos);
		if (data->forks)
			free(data->forks);
		if (message)
			printf("ERROR: %s\n", message);
	}
	return (1);
}

static void	free_philos(t_philo *philos)
{
	int	i;
	int	limit;

	i = -1;
	limit = philos->data->args[0];
	while (++i < limit)
	{
		if (philos[i].has_mutex == 1)
			pthread_mutex_destroy(&philos[i].eat_mutex);
	}
	free(philos);
}
