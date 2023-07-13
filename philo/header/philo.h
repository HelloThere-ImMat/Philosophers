/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:59:34 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/10 14:57:31 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>

///// INT VALUES /////

# define ARG_MIN_NBR	5
# define ARG_MAX_NBR	6
# define ASCII_SPACE	32
# define ASCII_TAB		9
# define ASCII_ZERO		48
# define ASCII_NULL		0

///// ERROR MESSAGE /////

# define TOO_MANY_ARGS		"Too many arguments"
# define NOT_ENOUGH_ARGS	"Not enough arguments"
# define ARG_INSTRUCTION	"this program takes 4 or 5 arguments"
# define NEGATIVE_ARG		"All arguments needs to be positive, change :"
# define OUT_OF_BOUNDS_ARG	"All arguments must fit into a size_t, change :"
# define NON_DIGIT_ARG		"All arguments must be numerical, change :"
# define THREAD_ERROR		"Error while creating thread"

///// PRINT MESSAGE /////

# define TAKEN_FORK			"has taken a fork"
# define EATING				"is eating"
# define SLEEPING			"is sleeping"
# define THINK				"is thinking"
# define DEAD				"died"

///// STRUCT /////

typedef struct s_philo
{
	void			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	manager_mutex;
	size_t			index;
	size_t			diner_count;
	time_t			t_last_diner;
	time_t			start_time;
	time_t			t_die;
	time_t			t_eat;
	time_t			t_sleep;
	size_t			eat_nbr;
	bool			with_eat_limit;
	bool			full;
}				t_philo;

typedef struct s_data
{
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo_tab;
	pthread_t		*philo_threads;
	pthread_t		manager;
	size_t			satiated_nbr;
	time_t			start_time;
	time_t			t_die;
	time_t			t_eat;
	time_t			t_sleep;
	size_t			eat_nbr;
	size_t			ph_nbr;
	bool			with_eat_limit;
	bool			stop;
	struct timeval	tv;
}				t_data;

// PHILO

int		main(int argc, char **argv);
void	print_message(t_philo *ph, char *message, size_t timestamp);

// CHECK ARG

int		check_arg(int argc, char **argv);

// LIB UTILS

int		ft_isdigit(int c);
long	ft_atol(const char *nptr);

// INIT

int		init(t_data *data, int argc, char **argv);

// INIT PHILO

int		init_threads(t_data *data);

// DINER

void	*diner_single(void *arg);
void	*diner(void *arg);

// FORKS

bool	grab_forks(t_philo *ph);
void	drop_forks(t_philo *ph);

// EAT

int		eating_state(t_philo *ph);

// MANAGER

void	*manager_routine(void *arg);
void	update_data_stop(t_data *data);

// STOP OR PRINT

bool	stop_or_print(t_data *data, t_philo *ph, char *message);

// TIME

void	ft_usleep(time_t time);
time_t	get_simulation_time(time_t start_time);
time_t	get_time(void);

#endif