/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:35:00 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/14 10:45:56 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (0);
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
		if (check_overflow(argv[i]) == -1)
			return (0);
	}
	return (1);
}

int	check_dead(t_philo *philo, long long die_time)
{
	pthread_mutex_lock(&philo->eat_mutex);
	if (get_time() - philo->last_eat_time > die_time)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	return (0);
}

int	check_death_status(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->philo_dead)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (0);
}

int	check_overflow(char *str)
{
	long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
		if (num > 2147483647)
			return (-1);
	}
	return ((int)num);
}
