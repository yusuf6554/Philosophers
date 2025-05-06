/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:39:22 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/06 14:09:20 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		handle_error(NULL, 0, E_INVARGNUM);
	data = malloc(sizeof(t_data));
	if (!data)
		handle_error(data, 0, E_MALLOC);
	if (argc == 5)
		data->args[4] = -1;
	handle_error(data, check_arguments(data, argv + 1, -1, -1), E_INVARG);
	handle_error(data, init_mutexes(data), E_MUTEXINIT);
	handle_error(data, init_philos(data), E_PHILOINIT);
	handle_error(data, init_threads(data), E_THREADINIT);
	if (data->philo_count != data->args[0] - 1)
		handle_error(data, 0, "Philosopher count mismatch");
	else
	{
		free_all(data);
		return (0);
	}
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
	i = 0;
	while (i++ < 4)
		if (!data->args[i])
			return (0);
	return (1);
}
