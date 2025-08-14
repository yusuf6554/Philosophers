/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:52:15 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/14 10:41:58 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

int	print_message(t_philo *philo, char *message, int id)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->start_time;
	if (!check_death_status(philo->data))
		printf("%lld %d %s\n", time, id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (1);
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->philos)
			free(data->philos);
		if (data->forks)
			free(data->forks);
	}
}

int	ft_atoi(const char *str)
{
	unsigned long long	num;
	int					sign;
	int					i;

	sign = 1;
	num = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sign);
}
