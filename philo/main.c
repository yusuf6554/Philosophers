/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:39:22 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/02 15:11:15 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	main_data;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (!check_arguments(argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	init_philo(&main_data, argc, argv);
	if (!main_data.philo)
	{
		printf("Error: Failed to initialize philosophers\n");
		return (1);
	}
	return (philo_main(&main_data));
}
