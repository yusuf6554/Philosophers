/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:36:11 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/15 12:55:07 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == -1)
		return (printf("Error: Invalid arguments"), 1);
	if (init(&data, argc, argv) == -1)
		return (free_all(&data, "Error: Initialization failed"), 1);
	if (start(&data) == -1)
		return (free_all(&data, "Error: Failed to start simulation"), 1);
	free_all(&data, NULL);
	return (0);
}
