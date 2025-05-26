/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:52:48 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/26 13:55:49 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long long	get_time(void)
{
	struct timeval		time;
	static int			started;
	static long long	start_time;
	long long			current_time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	current_time = (time.tv_sec * 1000 + time.tv_usec / 1000);
	if (!started)
	{
		start_time = current_time;
		started = 1;
	}
	if (current_time < start_time)
		return (-1);
	return (current_time - start_time);
}

int	ft_sleep(int time)
{
	long long	start_time;

	start_time = get_time();
	if (start_time == -1)
		return (0);
	while (get_time() - start_time < time)
	{
		usleep(100);
		if (get_time() == -1)
			return (0);
	}
	return (1);
}
