/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:00:36 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/07 15:02:36 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_status(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->status_mutex);
	status = data->status;
	pthread_mutex_unlock(&data->status_mutex);
	return (status);
}

void	set_status(t_data *data, int status)
{
	pthread_mutex_lock(&data->status_mutex);
	data->status = status;
	pthread_mutex_unlock(&data->status_mutex);
}
