/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:50:21 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/19 13:44:38 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(char *str)
{
	int					i;
	unsigned long long	num;

	i = 0;
	num = 0;
	while (str[i] == '\t' || str[i] == '\r' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	while (str[i] == '+')
		i++;
	while (str[i])
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num);
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
	i = -1;
	if (data->philos)
		while (++i < data->philo_count)
			if (data->philos[i].mutex_initialized == 1)
				pthread_mutex_destroy(&data->philos[i].eat_mutex);
	if (data->philos)
		free(data->philos);
	if (data->threads)
		free(data->threads);
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

void	print_message(char *message, t_data *data, int id)
{
	long long	time;

	pthread_mutex_lock(&data->print_mutex);
	time = get_time() - data->start_time;
	if (!is_dead(data))
		printf("%lld %d %s\n", time, id, message);
	pthread_mutex_unlock(&data->print_mutex);
}

void	ft_sleep(int ms)
{
	long long	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(100);
}
