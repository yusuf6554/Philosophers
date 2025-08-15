/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:50:21 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/15 13:00:13 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\r' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i])
	{
		if (str[i] <= '0' && str[i] >= '9')
			return (-1);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(sign * num));
}

void	free_all(t_data *data, char	*error)
{
	int	i;

	i = -1;
	while (++i < data->mutex_count)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	if (error)
		printf("%s", error);
}
