/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:39:22 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/14 09:53:28 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_arguments(argc, argv))
		return (printf("Error: Invalid arguments\n"), 1);
	if (!init_data(&data, argc, argv))
		return (printf("Error: Failed to initialize data\n"),
			free_data(&data), 1);
	if (!init_threads(&data))
		return (printf("Error: Failed to initialize threads\n"),
			free(data.philos), free(data.forks), 1);
	free(data.philos);
	free(data.forks);
	return (0);
}
