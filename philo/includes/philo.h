/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:49:45 by bhumeau           #+#    #+#             */
/*   Updated: 2024/06/27 15:08:14 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include "error_messages.h"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	id_mutex;
	pthread_mutex_t	m_left_fork;
	bool			left_fork;
	pthread_mutex_t	*m_right_fork;
	bool			*right_fork;
	int				eat_count;
	int				number_of_philosophers;
	size_t			last_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	bool			is_dead;
	bool			ready;
	int				nb_have_eaten;
	pthread_mutex_t	m_data;
	pthread_mutex_t	m_ready;
	pthread_mutex_t	m_print;
}	t_data;

int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
bool	initialize_struct(t_data *data, int argc, char **argv);
void	initialize_philos(t_data *data);
size_t	get_current_time(void);
void	*odd_routine(void *arg);
void	*even_routine(void *arg);
void	observer_routine(t_data *data, int nb_philos);
void	ft_msleep(size_t time);
void	print_message(char *message, t_philo *philo);

bool	get_mutex_bool(pthread_mutex_t *mutex, bool *value);
int		get_mutex_int(pthread_mutex_t *mutex, int *value);
size_t	get_mutex_size_t(pthread_mutex_t *mutex, size_t *value);

void	set_mutex_bool(pthread_mutex_t *mutex, bool *value, bool new_value);
void	set_mutex_int(pthread_mutex_t *mutex, int *value, int new_value);
void	set_mutex_size_t(pthread_mutex_t *mutex, size_t *value, size_t new_value);

#endif