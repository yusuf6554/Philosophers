/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:13:15 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/19 13:35:32 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->sim_mutex);
	pthread_mutex_unlock(&philo->data->sim_mutex);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	if (philo->id % 2)
		ft_sleep(1);
	while (1)
	{
		if (philo_main(philo) == -1)
			break;
	}
	return (NULL);
}

int	philo_main(t_philo *philo)
{
	if (is_dead(philo->data) == 1)
		return (-1);
	if (philo->data->philo_count > 1)
		philo_eat(philo);
	else
		philo_single(philo);
	print_message("is sleeping", philo->data, philo->id);
	ft_sleep(philo->data->time_to_sleep);
	philo_think(philo);
	return (1);
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message("has taken a fork", philo->data, philo->id);
		pthread_mutex_lock(philo->right_fork);
		print_message("has taken a fork", philo->data, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message("has taken a fork", philo->data, philo->id);
		pthread_mutex_lock(philo->left_fork);
		print_message("has taken a fork", philo->data, philo->id);
	}
	print_message("is eating", philo->data, philo->id);
	ft_sleep(philo->data->time_to_eat);
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

	print_message("is thinking", philo->data, philo->id);
	i = philo->data->time_to_die - (philo->data->time_to_eat
				+ philo->data->time_to_sleep);
	if (i < 0)
		i = 0;
	else
		i /= 2;
	ft_sleep(i);
}

void	philo_single(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork", philo->data, philo->id);
	ft_sleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
}
