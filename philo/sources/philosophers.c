/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:09:38 by bhumeau           #+#    #+#             */
/*   Updated: 2024/06/27 17:54:31 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/philo.h"

void	print_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	if (!get_mutex_bool(&philo->data->m_data, &philo->data->is_dead))
		printf(message, get_current_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->m_print);
}

void	*odd_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_mutex_bool(&philo->data->m_data, &philo->data->ready) == false)
		usleep(2);
	set_mutex_size_t(&philo->id_mutex, &philo->last_eat, get_current_time());
	print_message("%zu %d is thinking\n", philo);
	while (!get_mutex_bool(&philo->data->m_data, &philo->data->is_dead))
	{
		while (get_mutex_bool(&philo->m_left_fork, &philo->left_fork) == true)
			usleep(100);
		set_mutex_bool(&philo->m_left_fork, &philo->left_fork, true);
		print_message("%zu %d has taken a fork\n", philo);
		while (get_mutex_bool(philo->m_right_fork, philo->right_fork) == true)
			usleep(5);
		set_mutex_bool(philo->m_right_fork, philo->right_fork, true);
		print_message("%zu %d has taken a fork\n", philo);
		set_mutex_size_t(&philo->id_mutex, &philo->last_eat, get_current_time());
		print_message("%zu %d is eating\n", philo);
		ft_msleep(philo->time_to_eat);
		set_mutex_int(&philo->id_mutex, &philo->eat_count, philo->eat_count + 1);
		set_mutex_bool(&philo->m_left_fork, &philo->left_fork, false);
		set_mutex_bool(philo->m_right_fork, philo->right_fork, false);
		print_message("%zu %d is sleeping\n", philo);
		ft_msleep(philo->time_to_sleep);
		print_message("%zu %d is thinking\n", philo);
		ft_msleep(5);
	}
	return (0);
}

void	*even_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_mutex_bool(&philo->data->m_data, &philo->data->ready) == false)
		usleep(2);
	set_mutex_size_t(&philo->id_mutex, &philo->last_eat, get_current_time());
	print_message("%zu %d is thinking\n", philo);
	ft_msleep(20);
	while (!get_mutex_bool(&philo->data->m_data, &philo->data->is_dead))
	{
		while (get_mutex_bool(philo->m_right_fork, philo->right_fork) == true)
			usleep(100);
		set_mutex_bool(philo->m_right_fork, philo->right_fork, true);
		print_message("%zu %d has taken a fork\n", philo);
		while (get_mutex_bool(&philo->m_left_fork, &philo->left_fork) == true)
			usleep(5);
		set_mutex_bool(&philo->m_left_fork, &philo->left_fork, true);
		print_message("%zu %d has taken a fork\n", philo);
		set_mutex_size_t(&philo->id_mutex, &philo->last_eat, get_current_time());
		print_message("%zu %d is eating\n", philo);
		ft_msleep(philo->time_to_eat);
		set_mutex_int(&philo->id_mutex, &philo->eat_count, philo->eat_count + 1);
		set_mutex_bool(philo->m_right_fork, philo->right_fork, false);
		set_mutex_bool(&philo->m_left_fork, &philo->left_fork, false);
		print_message("%zu %d is sleeping\n", philo);
		ft_msleep(philo->time_to_sleep);
		print_message("%zu %d is thinking\n", philo);
		ft_msleep(5);
	}
	return (0);
}
