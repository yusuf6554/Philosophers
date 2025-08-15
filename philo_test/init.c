/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:36:52 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/15 14:00:22 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (data->misc_mutex_count = 1, -1);
	if (pthread_mutex_init(&data->sim_mutex, NULL))
		return (data->misc_mutex_count = 2, -1);
	data->misc_mutex_count = 3;
	return (1);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (-1);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (-1);
		data->fork_count++;
	}
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (-1);
	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = get_time();
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		data->philos[i].data = data;
	}
	return (1);
}

int	init(t_data *data, int argc, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	data->start_time = get_time();
	data->misc_mutex_count = 0;
	if (init_mutexes(data) == -1)
		return (-1);
	data->fork_count = 0;
	if (init_forks(data) == -1)
		return (-1);
	if (init_philos(data) == -1)
		return (-1);
}


