/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:34:26 by yukoc             #+#    #+#             */
/*   Updated: 2025/04/30 13:47:12 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <inttypes.h>
# include <stdint.h>

typedef struct s_philo
{
	int				id;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				is_dead;
	int				eat_count;
	pthread_t		thread;
	pthread_t		eat_thread;
	pthread_t		death_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*die_mutex;
}			t_philo;

typedef struct s_data
{
	t_philo		*philo;
}			t_data;

#endif