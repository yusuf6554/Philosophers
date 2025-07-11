/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:52:15 by yukoc             #+#    #+#             */
/*   Updated: 2025/07/11 13:52:08 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	variable_ops(pthread_mutex_t *mutex, int *variable, int value, int type)
{
	pthread_mutex_lock(mutex);
	if (type == 0)
		*variable = value;
	else
		value = *variable;
	pthread_mutex_unlock(mutex);
	if (type == 1)
	{
		variable = &value;
		return (value);
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	life_check(t_philo *philo, t_data *data)
{
	if (philo->eat_count == data->args[4]
		|| variable_ops(&data->dead_mutex, &data->philo_dead, -1, GETVALUE))
		return (0);
	else
		return (1);
}
