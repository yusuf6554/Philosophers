/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:34:26 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/11 14:29:09 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define E_INVARG "Invalid arguments"
# define E_PHILOINIT "Philosopher initialization failed"
# define E_MUTEXINIT "Mutex initialization failed"
# define E_INVARGNUM "Invalid number of arguments"

typedef struct s_philo
{
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_mutex;
	pthread_t		thread;
	int				id;
	int				has_mutex;
	int				eat_count;
	long long		last_eat_time;
}			t_philo;

typedef struct s_data
{
	int				status;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	status_mutex;
	t_philo			*philos;
	long long		args[5];
	int				philo_count;
	int				philo_dead;
	int				mutex_error;
	long long		start_time;
}			t_data;

int			init_threads(t_data *data);
int			handle_error(t_data *data, int error_code, char *message);
long long	get_time(void);
int			ft_sleep(int time);
int			ft_strcmp(char *s1, char *s2);
int			print_message(t_philo *philo, char *message);
int			get_status(t_data *data);
void		set_status(t_data *data, int status);
int			check_dead(t_philo *philo, long long die_time);
int			check_death_status(t_data *data);
void		*philo_routine(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_fork_lock(t_philo *philo);
int			monitoring(t_data *data);
int			monitor_deaths(t_data *data);
int			monitor_eat_count(t_data *data);

#endif