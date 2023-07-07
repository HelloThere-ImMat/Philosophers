/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:48:21 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/07 18:39:02 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

void	*diner_single(void *arg)
{
	t_philo	*ph;
	t_data	*data;

	ph = (t_philo *)arg;
	data = (t_data *)ph->data;
	pthread_mutex_lock(&data->simulation_mutex);
	ph->start_time = data->start_time;
	ph->t_last_diner = ph->start_time;
	pthread_mutex_unlock(&data->simulation_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%zu %zu %s\n", get_simulation_time(ph->start_time),
		ph->index, TAKEN_FORK);
	pthread_mutex_unlock(&data->print_mutex);
	ft_usleep(ph->t_die);
	print_message(ph, DEAD, get_simulation_time(ph->start_time));
	update_data_stop(data);
	return (NULL);
}

static int	philo_loop(t_philo *ph, t_data *data)
{
	if (ph->full == false)
	{
		if (grab_forks(ph) == false
			|| eating_state(ph) == EXIT_FAILURE
			|| stop_or_print(data, ph, THINK) == true)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*diner(void *arg)
{
	t_philo	*ph;
	t_data	*data;

	ph = (t_philo *)arg;
	data = (t_data *)ph->data;
	pthread_mutex_lock(&data->simulation_mutex);
	ph->start_time = data->start_time;
	pthread_mutex_unlock(&data->simulation_mutex);
	if (ph->index % 2 == 0)
		ft_usleep(ph->t_eat / 10);
	ph->t_last_diner = ph->start_time;
	while (1)
	{
		if (philo_loop(ph, data) == EXIT_FAILURE)
			break ;
	}
	return (NULL);
}
