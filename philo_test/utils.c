/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:50:21 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/15 13:50:47 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

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
	while (++i < data->fork_count)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	if (data->misc_mutex_count >= 1)
		pthread_mutex_destroy(&data->print_mutex);
	if (data->misc_mutex_count >= 2)
		pthread_mutex_destroy(&data->death_mutex);
	if (data->misc_mutex_count >= 3)
		pthread_mutex_destroy(&data->sim_mutex);
	if (error)
		printf("%s", error);
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
