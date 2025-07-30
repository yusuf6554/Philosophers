/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:34:26 by yukoc             #+#    #+#             */
/*   Updated: 2025/07/30 14:00:22 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define E_INVARG "Invalid arguments"
# define E_PHILOINIT "Philosopher initialization failed"
# define E_MUTEXINIT "Mutex initialization failed"
# define E_INVARGNUM "Invalid number of arguments"

typedef struct s_data
{
	int				philo_num;
	int				life_time;
	int				eat_time;
	int				sleep_time;
	int				eat_count;
	int				dead;
	int				thrd_count;
	int				ready;
	long long		start_time;
	pthread_mutex_t	general_mutex;
	pthread_mutex_t	philo_must_eat_mutex;
	pthread_mutex_t	thread_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;
}			t_data;

typedef struct s_philo
{
	int				philo_id;
	int				philo_loop;
	long long		last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t philo_last_eat_mutex;
	pthread_t		thread;
	t_data			*data;
}			t_philo;

int				arg_check(int argc, char **argv);
int				init_data(t_data *data, char **argv);
int				init_mutex(t_data *data);
void			destroy_mutex(t_data *data);
pthread_mutex_t	*init_forks(t_data *data);
void			destroy_forks(pthread_mutex_t *forks, t_data *data, int i);
t_philo			*init_philos(t_data *data, pthread_mutex_t *forks);
void			destroy_philo(t_philo *philo, pthread_mutex_t *forks,
					t_data *data, int i);
void			destroy(t_data *data, t_philo *philo, pthread_mutex_t *forks);
void			flag_data(pthread_mutex_t *mutex, int *dst, int val);
void			set_int(pthread_mutex_t *mutex, int *dst, int val);
void			get_int(pthread_mutex_t *mutex, int *val);
void			set_long(pthread_mutex_t *mutex, long long *dst, long long val);
void			get_long(pthread_mutex_t *mutex, long long *val);
void			print_message(t_philo *philo, const char *message);
void			wait_for_threads(t_data *data);
int				all_philos_ate(t_philo *philo);
void			ft_usleep(int time);
long long		get_time(void);
int				start_simulation(t_data *data, t_philo *philo);
long			ft_atol(char *str);
int				ft_isdigit(int c);
void			main_activities(t_philo *philo);
void			single_philo(t_philo *philo);
void			print_error(const char *message);
void			ft_bzero(void *s, size_t n);

#endif
