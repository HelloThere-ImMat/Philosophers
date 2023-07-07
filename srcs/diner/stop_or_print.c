/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_or_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:38:45 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/07 18:25:59 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

bool	stop_or_print(t_data *data, t_philo *ph, char *message)
{
	pthread_mutex_lock(&data->simulation_mutex);
	if (data->stop == true)
	{
		pthread_mutex_unlock(&data->simulation_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->simulation_mutex);
	if (ph->with_eat_limit == true && ph->full == true)
	{
		pthread_mutex_lock(&data->simulation_mutex);
		data->satiated_nbr++;
		pthread_mutex_unlock(&data->simulation_mutex);
		return (true);
	}
	if (message != NULL)
		print_message(ph, message, get_simulation_time(ph->start_time));
	return (false);
}
