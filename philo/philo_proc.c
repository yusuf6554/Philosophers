/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:55:14 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/20 14:04:14 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	init_threads(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philos;
	i = 0;
	if (data->philo_dead)
		return (1);
	pthraed_mutex_lock(&data->ready_mutex);
	while (i < data->args[0])
	{
		if (pthread_create(&philo[i].thread, NULL,
			(void *)philo_routine, &philo[i]))
			break ;
		data->philo_count = i++;
	}
	pthread_mutex_unlock(&data->ready_mutex);
	death_check(data);
	i = -1;
	while (++i < data->args[0])
		if (pthread_join(philo[i].thread, NULL))
			break ;
	return (0);
}

void	*philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ready_mutex);
	pthread_mutex_unlock(&philo->data->ready_mutex);
	if (philo->data->philo_count != philo->data->args[0] - 1)
		return (NULL);
	if (philo->data->args[0] == 1)
	{
		print_message(philo, "has taken a fork");
		ft_sleep(philo->data->args[1]);
		print_message(philo, "died");
		return (NULL);
	}
	if (!(philo->id % 2))
		ft_sleep(philo->data->args[2]);
	while (!var_int(&philo->data->dead_mutex, &philo->data->philo_dead, -1, 1))
		if (!loop(philo, philo->data))
			break ;
	return (NULL);
}
