/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mat <mat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:22:22 by mdorr             #+#    #+#             */
/*   Updated: 2023/06/26 14:32:41 by mat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

time_t	get_simulation_time(time_t start_time)
{
	return (get_time() - start_time);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(time_t time)
{
	time_t	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(10);
}
