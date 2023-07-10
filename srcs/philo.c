/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:15:29 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/10 14:35:10 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	print_message(t_philo *ph, char *message, size_t timestamp)
{
	t_data	*data;

	data = ph->data;
	pthread_mutex_lock(&data->print_mutex);
	if (data->stop == false)
		printf("%zu %zu %s\n", timestamp, ph->index, message);
	pthread_mutex_unlock(&data->print_mutex);
}

static void	free_manager(t_data data)
{
	size_t	i;

	i = 0;
	free(data.philo_threads);
	while (i < data.ph_nbr)
	{
		pthread_mutex_destroy(&data.philo_tab[i].manager_mutex);
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.simulation_mutex);
	free(data.philo_tab);
	free(data.forks);
}

static void	join_threads(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->ph_nbr)
		pthread_join(data->philo_threads[i++], NULL);
	pthread_join(data->manager, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_arg(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init(&data, argc, argv) == EXIT_FAILURE)
	{
		free_manager(data);
		return (EXIT_FAILURE);
	}
	join_threads(&data);
	free_manager(data);
	return (EXIT_SUCCESS);
}
