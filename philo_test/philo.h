/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:34:26 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/15 14:01:49 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_t		monitor_thread;
	int				thread_count;
	int				fork_count;
	int				misc_mutex_count;
}			t_data;

int			check_args(int argc, char **argv);
int			check_is_integer(char *num);

int			ft_atoi(char *str);
void		free_all(t_data *data, char	*error);
long long	get_time(void);

int			init_mutexes(t_data *data);
int			init_forks(t_data *data);
int			init_philos(t_data *data);
int			init(t_data *data, int argc, char **argv);

#endif