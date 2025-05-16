/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:34:26 by yukoc             #+#    #+#             */
/*   Updated: 2025/05/16 12:59:38 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <inttypes.h>
# include <stdint.h>

# define E_INVARG "Invalid arguments"
# define E_PHILOINIT "Philosopher initialization failed"
# define E_THREADINIT "Thread initialization failed"
# define E_MUTEXINIT "Mutex initialization failed"
# define E_INVARGNUM "Invalid number of arguments"
# define E_MALLOC "Memory allocation failed"
# define E_PHCNTMISMATCH "Philosopher count mismatch"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	int				id;
	int				eat_count;
	long long		last_eat_time;
}			t_philo;

typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	ready_mutex;
	t_philo			*philos;
	long long		args[5];
	int				philo_count;
	int				philo_dead;
	int				mutex_error;
}			t_data;

#endif