/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:34:26 by yukoc             #+#    #+#             */
/*   Updated: 2025/06/10 15:41:22 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <inttypes.h>
# include <stdint.h>

# define E_INVARG "Invalid arguments"
# define E_PHILOINIT "Philosopher initialization failed"
# define E_MUTEXINIT "Mutex initialization failed"
# define E_INVARGNUM "Invalid number of arguments"

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

int			init_threads(t_data *data);
void		*philo_routine(t_philo *philo);
int			handle_error(t_data *data, int error_code, char *message);
long long	get_time(void);
int			ft_sleep(int time);
int			variable_ops(pthread_mutex_t *mutex, int *variable,
				int value, int operation);
int			ft_strcmp(char *s1, char *s2);
int			life_check(t_philo *philo, t_data *data);
int			death_check(t_data *data);

#endif