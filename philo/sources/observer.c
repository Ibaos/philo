/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:01:29 by bhumeau           #+#    #+#             */
/*   Updated: 2024/06/27 17:16:20 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/philo.h"

bool	verify_death(t_data *data, int nb_philos)
{
	int		i;

	i = 0;
	while (i < nb_philos)
	{
		if (-get_mutex_size_t(&data->philos[i].id_mutex, &data->philos[i].last_eat) + get_current_time() > data->time_to_die)
		{
			print_message("%zu %d died\n", &data->philos[i]);
			set_mutex_bool(&data->m_data, &data->is_dead, true);
			return (true);
		}
		i++;
	}
	return (false);
}

void	observer_routine(t_data *data, int nb_philos)
{
	int		i;

	ft_msleep(10);
	while (42)
	{
		if (verify_death(data, nb_philos))
			break ;
		if (data->number_of_times_each_philosopher_must_eat != -1)
		{
			i = 0;
			data->nb_have_eaten = 0;
			while (i < nb_philos)
			{
				if (get_mutex_int(&data->philos[i].id_mutex, &data->philos[i].eat_count) >= data->number_of_times_each_philosopher_must_eat)
					data->nb_have_eaten++;
				i++;
			}
			if (data->nb_have_eaten == nb_philos)
				break ;
		}
		usleep(250);
	}
	set_mutex_bool(&data->m_data, &data->is_dead, true);
}
