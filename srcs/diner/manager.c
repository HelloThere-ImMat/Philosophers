/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:48:23 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/07 18:38:56 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

void	update_data_stop(t_data *data)
{
	pthread_mutex_lock(&data->simulation_mutex);
	data->stop = true;
	pthread_mutex_unlock(&data->simulation_mutex);
}

static int	manager_loop(t_data *data,
					size_t philo_nbr,
					size_t start_time,
					time_t t_die)
{
	size_t	i;

	i = 0;
	while (i < philo_nbr)
	{
		pthread_mutex_lock(&data->philo_tab[i].manager_mutex);
		if (get_simulation_time(start_time)
			- data->philo_tab[i].t_last_diner > t_die)
		{
			update_data_stop(data);
			print_message(&data->philo_tab[i], DEAD,
				get_simulation_time(data->philo_tab[i].start_time));
			return (EXIT_SUCCESS);
		}
		pthread_mutex_unlock(&data->philo_tab[i++].manager_mutex);
	}
	pthread_mutex_lock(&data->simulation_mutex);
	if (data->satiated_nbr == data->ph_nbr)
	{
		pthread_mutex_unlock(&data->simulation_mutex);
		update_data_stop(data);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&data->simulation_mutex);
	return (EXIT_FAILURE);
}

void	*manager_routine(void *arg)
{
	t_data	*data;
	size_t	philo_nbr;
	time_t	start_time;
	time_t	t_die;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->simulation_mutex);
	philo_nbr = data->ph_nbr;
	start_time = data->start_time;
	t_die = data->t_die;
	pthread_mutex_unlock(&data->simulation_mutex);
	while (1)
	{
		if (manager_loop(data, philo_nbr, start_time, t_die) == EXIT_SUCCESS)
			break ;
	}
	return (NULL);
}
