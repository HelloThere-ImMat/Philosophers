/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:21:40 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/07 17:39:44 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

static int	init_clock(t_data *data)
{
	if (gettimeofday(&(data->tv), NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	data->with_eat_limit = false;
	data->eat_nbr = 0;
	data->stop = false;
	data->satiated_nbr = 0;
	data->ph_nbr = ft_atol(argv[1]);
	data->t_die = ft_atol(argv[2]);
	data->t_eat = ft_atol(argv[3]);
	data->t_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		data->with_eat_limit = true;
		data->eat_nbr = ft_atol(argv[5]);
	}
	data->philo_threads = malloc(sizeof(pthread_t) * data->ph_nbr);
	if (data->philo_threads == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init(t_data *data, int argc, char **argv)
{
	if (pthread_mutex_init(&data->simulation_mutex, NULL) != 0
		|| pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&data->simulation_mutex);
	if (init_data(data, argc, argv) == EXIT_FAILURE
		|| init_clock(data) == EXIT_FAILURE
		|| init_threads(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->start_time = get_time();
	pthread_mutex_unlock(&data->simulation_mutex);
	return (EXIT_SUCCESS);
}
