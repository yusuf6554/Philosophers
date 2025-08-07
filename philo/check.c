/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:35:00 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/07 15:36:52 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
