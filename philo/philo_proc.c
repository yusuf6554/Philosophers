/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:55:14 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/07 15:41:54 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*philo_routine(t_philo *philo)
{
	while (get_status(philo->data) == 0)
		;
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	if (philo->id % 2)
		ft_sleep(1);
	while (!check_death_status(philo->data))
	{
		philo_eat(philo);
		print_message(philo, "is sleeping");
		ft_sleep(philo->data->args[3]);
		philo_think(philo);
	}
}

void	philo_fork_lock(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		ft_sleep(philo->data->args[1]);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	philo_fork_lock(philo);
	print_message(philo, "is eating");
	ft_sleep(philo->data->args[2]);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_think(t_philo *philo)
{
	int	i;

	print_message(philo, "is thinking");
	i = (philo->data->args[1] - (philo->data->args[3]
				+ philo->data->args[2])) / 2;
	if (i < 0)
		i = 0;
	ft_sleep(i);
}

int	print_message(t_philo *philo, char *message)
{
	long long	time;
	t_data		*data;

	data = philo->data;
	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->start_time;
	printf("%lld %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (1);
}
