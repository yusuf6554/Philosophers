/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:36:55 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/19 13:41:38 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	check_args(int argc, char **argv)
{
	int		i;

	if (argc != 5 && argc != 6)
		return (-1);
	i = 0;
	while (argv[++i])
	{
		if (check_is_integer(argv[i]) == -1)
			return (-1);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (-1);
	return (1);
}

int	check_is_integer(char *num)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	while (num[i] == '\t' || num[i] == '\r' || num[i] == '\n'
		|| num[i] == '\v' || num[i] == '\f' || num[i] == ' ')
		i++;
	while (num[i] == '+')
		i++;
	while (num[i])
	{
		if (num[i] <= '0' && num[i] >= '9')
			return (-1);
		n = n * 10 + (num[i] - '0');
		i++;
	}
	if (n > 2147483647)
		return (-1);
	return (1);
}

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->is_dead == 1)
		return (pthread_mutex_unlock(&data->death_mutex), 1);
	return (pthread_mutex_unlock(&data->death_mutex), 0);
}

int	death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	if (get_time() - philo->last_eat_time > philo->data->time_to_die)
		return (pthread_mutex_unlock(&philo->eat_mutex), 1);
	return (pthread_mutex_unlock(&philo->eat_mutex), 0);
}
