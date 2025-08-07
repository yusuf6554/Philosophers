/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:52:15 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/07 15:40:51 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	set_int(pthread_mutex_t *mutex, int	*dst, int val)
{
	pthread_mutex_lock(mutex);
	*dst = val;
	pthread_mutex_unlock(mutex);
}

int	get_int(pthread_mutex_t *mutex, int *src)
{
	int	result;

	pthread_mutex_lock(mutex);
	result = *src;
	pthread_mutex_unlock(mutex);
	return (result);
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
