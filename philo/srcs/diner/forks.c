/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:35:04 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/10 14:37:30 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

bool	grab_forks(t_philo *ph)
{
	time_t	timestamp;

	if (ph->index % 2 == 0)
	{
		pthread_mutex_lock(ph->right_fork);
		pthread_mutex_lock(ph->left_fork);
	}
	else
	{
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
	}
	timestamp = get_simulation_time(ph->start_time);
	if (stop_or_print(ph->data, ph, TAKEN_FORK) == true)
	{
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		return (false);
	}
	print_message(ph, TAKEN_FORK, timestamp);
	return (true);
}

void	drop_forks(t_philo *ph)
{
	if (ph->index % 2 == 0)
	{
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
	}
	else
	{
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
	}
}
