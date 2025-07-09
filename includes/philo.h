/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:41 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/09 18:05:33 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <limits.h> //INT_MAX
# include <pthread.h> // mutex: init, destroy, lock, unlock
					// threads: create, join, detach

typedef struct s_table	t_table;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	m_fork;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				is_full;
	pthread_t		thread;
	t_table			*table;
	t_fork			*left_fork;
	t_fork			*right_fork;
	unsigned long	t_last_meal;
	pthread_mutex_t	t_last_meal_mut;
	pthread_mutex_t	meals_eaten_mut;
}	t_philo;

typedef struct s_table
{
	int							n_philo;
	int							n_philo_full;
	unsigned long long			time_die;
	int							time_eat;
	int							time_sleep;
	int							n_meal;
	unsigned long				start_time;
	t_philo						*philo;
	t_fork						*forks;
	pthread_t					monitor;
	int							end_simulation;
	pthread_mutex_t				write_mutex;
	pthread_mutex_t				end_simulation_mut;
}	t_table;

//parse_args.c
int						parse_args(int argc, char **argv, t_table *table);

//utils.c
unsigned long long int	get_time(void);
unsigned long long int	get_elapsed_time(t_table *table);
void					safe_print(char *str, t_philo *philo);
int						check_one_philo(t_table *table);
int						check_end_simulation(t_table *table);

//mutex.c
void					init_mutex(t_table *table);
void					destroy_mutex(t_table *table);

//philo_routine.c
void					*monitor_routine(void *table_arg);
void					*philo_routine(void *philo_arg);

//init.c
int						init_philos(t_table *table);
int						init_table(t_table *table);
void					precise_sleep(long time, t_table *table);

#endif