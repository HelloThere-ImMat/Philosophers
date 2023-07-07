/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:36:22 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/07 18:20:24 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

int	eating_state(t_philo *ph)
{
	print_message(ph, EATING, get_simulation_time(ph->start_time));
	ph->t_last_diner = get_simulation_time(ph->start_time);
	ft_usleep(ph->t_eat);
	ph->diner_count++;
	if (ph->diner_count == ph->eat_nbr)
		ph->full = true;
	drop_forks(ph);
	if (stop_or_print(ph->data, ph, SLEEPING) == true)
		return (EXIT_FAILURE);
	ft_usleep(ph->t_sleep);
	return (EXIT_SUCCESS);
}
