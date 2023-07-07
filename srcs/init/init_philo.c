/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:22:38 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/07 17:45:14 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

static int	init_forks(t_data *data, t_philo *philo_tab)
{
	pthread_mutex_t	*forks;
	size_t			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->ph_nbr);
	data->forks = forks;
	if (forks == NULL)
		return (EXIT_FAILURE);
	while (i < data->ph_nbr)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks);
			return (EXIT_FAILURE);
		}
		philo_tab[i].left_fork = &forks[i];
		if (i != 0)
			philo_tab[i].right_fork = &forks[i - 1];
		i++;
	}
	philo_tab[0].right_fork = &forks[i - 1];
	return (EXIT_SUCCESS);
}

static int	fill_philo(t_data *data, t_philo *philo, size_t i)
{
	philo->data = data;
	philo->index = i + 1;
	philo->diner_count = 0;
	philo->t_die = data->t_die;
	philo->t_eat = data->t_eat;
	philo->t_sleep = data->t_sleep;
	philo->eat_nbr = data->eat_nbr;
	philo->with_eat_limit = data->with_eat_limit;
	philo->full = false;
	if (pthread_mutex_init(&philo->manager_mutex, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_philo	*init_philo(t_data *data)
{
	size_t	i;
	t_philo	*philo_tab;

	i = 0;
	philo_tab = malloc(sizeof(t_philo) * data->ph_nbr);
	if (philo_tab == NULL)
		return (NULL);
	while (i < data->ph_nbr)
	{
		if (fill_philo(data, &philo_tab[i], i) == EXIT_FAILURE)
		{
			free(philo_tab);
			return (NULL);
		}
		i++;
	}
	if (init_forks(data, philo_tab) == EXIT_FAILURE)
		return (free(philo_tab), NULL);
	return (philo_tab);
}

static int	thread_error(void)
{
	printf("%s\n", THREAD_ERROR);
	return (EXIT_FAILURE);
}

int	init_threads(t_data *data)
{
	size_t	i;

	data->philo_tab = init_philo(data);
	printf("data ph - nbr is %zu\n", data->ph_nbr);
	if (data->philo_tab == NULL)
		return (EXIT_FAILURE);
	i = 0;
	if (data->ph_nbr == 1)
	{
		if (pthread_create(&data->philo_threads[i],
				NULL, diner_single, &data->philo_tab[i]) != 0)
			return (thread_error());
	}
	else
	{
		while (i < data->ph_nbr)
		{
			if (pthread_create(&data->philo_threads[i], NULL,
					diner, &data->philo_tab[i]) != 0)
				return (thread_error());
			i++;
		}
	}
	if (pthread_create(&data->manager, NULL, manager_routine, data) != 0)
		return (thread_error());
	return (EXIT_SUCCESS);
}
