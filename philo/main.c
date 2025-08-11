/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:39:22 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/11 14:26:25 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

static int	check_arguments(t_data *data, char **argv, int i, int j);
static int	init_philos(t_data *data);
static int	init_mutexes(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		handle_error(&data, 0, E_INVARGNUM);
	if (argc == 5)
		data.args[4] = -1;
	data.status = 0;
	handle_error(&data, check_arguments(&data, argv + 1, -1, -1), E_INVARG);
	handle_error(&data, init_mutexes(&data), E_MUTEXINIT);
	handle_error(&data, init_philos(&data), E_PHILOINIT);
	handle_error(&data, init_threads(&data), NULL);
	if (data.philo_count != data.args[0])
		return (1);
	else
		return (0);
}

static int	check_arguments(t_data *data, char **argv, int i, int j)
{
	if (data->philo_dead)
		return (1);
	while (argv[++i])
	{
		j = -1;
		while (argv[i][0] == '0')
			argv[i]++;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			data->args[i] = data->args[i] * 10 + (argv[i][j] - '0');
		}
		if (data->args[i] > 2147483647)
			return (0);
	}
	if (data->args[0] < 1 || data->args[1] < 1 || data->args[2] < 1
		|| data->args[3] < 1 || data->args[4] == 0)
		return (0);
	return (1);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	if (data->philo_dead)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->args[0]);
	if (!data->philos)
		return (0);
	memset(data->philos, 0, sizeof(t_philo) * data->args[0]);
	while (++i < data->args[0])
	{
		if (pthread_mutex_init(&data->philos[i].eat_mutex, NULL))
			return (data->philos[i].has_mutex = 0, 0);
		data->philos[i].has_mutex = 1;
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_eat_time = get_time();
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->args[0]];
	}
	return (1);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	if (data->philo_dead)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->args[0]);
	if (!data->forks)
		return (0);
	memset(data->forks, 0, sizeof(pthread_mutex_t) * data->args[0]);
	while (++i < data->args[0])
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
	}
	if (pthread_mutex_init(&data->dead_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (data->mutex_error = 1, 0);
	if (pthread_mutex_init(&data->ready_mutex, NULL))
		return (data->mutex_error = 2, 0);
	return (data->mutex_error = 3, 1);
}
