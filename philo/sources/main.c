/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:51:42 by bhumeau           #+#    #+#             */
/*   Updated: 2024/06/27 17:28:46 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/philo.h"

void	free_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	while (--i >= 0)
	{
		pthread_mutex_destroy(&data->philos[i].m_left_fork);
		pthread_mutex_destroy(&data->philos[i].id_mutex);
	}
	pthread_mutex_destroy(&data->m_data);
	pthread_mutex_destroy(&data->m_ready);
	pthread_mutex_destroy(&data->m_print);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf(ARGC_ERROR);
		return (1);
	}
	if (!initialize_struct(&data, argc, argv))
		return (1);
	data.philos = malloc(sizeof(t_philo) * data.number_of_philosophers);
	if (!data.philos)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (1);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		printf("%d 1 died\n", ft_atoi(argv[2]) + 1);
		return (0);
	}
	initialize_philos(&data);
	set_mutex_size_t(&data.m_data, &data.start_time, get_current_time());
	set_mutex_bool( &data.m_data, &data.ready, true);
	ft_msleep(50);
	observer_routine(&data, get_mutex_int(&data.m_data, &data.number_of_philosophers));
	ft_msleep(100);
	free_and_destroy(&data);
	free(data.philos);
	return (0);
}
