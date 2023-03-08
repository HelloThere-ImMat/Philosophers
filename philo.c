/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:49:42 by mdorr             #+#    #+#             */
/*   Updated: 2023/03/07 12:17:28 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

typedef struct s_data
{
	pthread_mutex_t	mutex;
	int				shared_variable;
	int				i;
}				t_data;

void	*my_function(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->mutex);
	data->shared_variable++;
	printf("Thread %d incremented shared variable to %d\n",
		data->i, data->shared_variable);
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

int	main(void)
{
	t_data			data;
	pthread_t		thread1;
	pthread_t		thread2;

	data.shared_variable = 0;
	data.i = 1;
	pthread_mutex_init(&data.mutex, NULL);
	pthread_create(&thread1, NULL, my_function, (void *)&data);
	data.i++;
	pthread_create(&thread2, NULL, my_function, (void *)&data);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&data.mutex);
	return (0);
}
