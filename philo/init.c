/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:22:10 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/14 10:55:34 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

int	init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->args[0]);
	if (!philos)
		return (0);
	i = -1;
	while (++i < data->args[0])
	{
		if (pthread_mutex_init(&philos[i].eat_mutex, NULL))
			return (free(philos), 0);
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].last_eat_time = get_time();
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->args[0]];
		philos[i].eat_count = 0;
	}
	data->philos = philos;
	return (1);
}

int	init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * data->args[0]);
	if (!forks)
		return (0);
	i = -1;
	while (++i < data->args[0])
		if (pthread_mutex_init(&forks[i], NULL))
			return (free(forks), 0);
	data->forks = forks;
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->args[0] = ft_atoi(argv[1]);
	data->args[1] = ft_atoi(argv[2]);
	data->args[2] = ft_atoi(argv[3]);
	data->args[3] = ft_atoi(argv[4]);
	if (argc == 6)
		data->args[4] = ft_atoi(argv[5]);
	else
		data->args[4] = -1;
	data->forks = NULL;
	data->philos = NULL;
	if (data->args[0] <= 0 || data->args[1] <= 0 || data->args[2] <= 0
		|| (argc == 6 && data->args[4] <= 0))
		return (0);
	if (pthread_mutex_init(&data->dead_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->status_mutex, NULL))
		return (0);
	data->philo_dead = 0;
	data->status = 0;
	if (!init_forks(data) || !init_philos(data))
		return (0);
	return (1);
}

int	init_threads(t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = -1;
	while (++i < data->args[0])
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, (void *)&data->philos[i]))
			return (0);
	if (pthread_create(&monitor_thread, NULL, monitoring, (void *)data))
		return (0);
	if (pthread_join(monitor_thread, NULL))
		return (0);
	i = -1;
	while (++i < data->args[0])
		if (pthread_join(data->philos[i].thread, NULL))
			break ;
	return (1);
}
