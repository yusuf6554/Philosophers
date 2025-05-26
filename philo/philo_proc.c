/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:55:14 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/26 14:02:20 by yukoc            ###   ########.fr       */
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
	while (!variable_ops(&philo->data->dead_mutex,
		&philo->data->philo_dead, -1, 1))
		if (!philo_loop(philo, philo->data))
			break ;
	return (NULL);
}

static int	philo_loop(t_philo *philo, t_data *data)
{
	if (!life_check(philo, data))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (!print_message(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->left_fork), 0);
	pthread_mutex_lock(philo->right_fork);
	if (!print_message(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 0);
	if (!print_message(philo, "is eating"))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 0);
	pthread_mutex_lock(&data->eat_mutex);
	philo->last_eat_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&data->eat_mutex);
	ft_sleep(data->args[2]);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!print_message(philo, "is sleeping"))
		return (0);
	ft_sleep(data->args[3]);
	if (!print_message(philo, "is thinking"))
		return (0);
	return (1);
}

static int	print_message(t_philo *philo, const char *message)
{
	long long	time;
	t_data		*data;

	data = philo->data;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!life_check(philo, data))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (0);
	}
	if (!ft_strcmp(message, "died"))
		variable_ops(&data->dead_mutex, &data->philo_dead, 1, 1);
	time = get_time() - philo->data->args[4];
	printf("%lld %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (1);
}
