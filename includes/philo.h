/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:41 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/04 16:23:23 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <limits.h> //INT_MAX
# include <pthread.h> // mutex: init, destroy, lock, unlock
					// threads: create, join, detach

typedef struct s_table	t_table;

typedef struct	s_fork
{
	int	fork_id;
	pthread_mutex_t	m_fork;
}	t_fork;


typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	pthread_t		thread;
	t_table			*table;
	t_fork			*left_fork;
	t_fork			*right_fork;
	unsigned long	last_meal;
	int				died;
	pthread_mutex_t	m_last_meal;
}	t_philo;

typedef struct s_table
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
	unsigned long	start_time;
	t_philo			*philo;
	t_fork			*forks;
	pthread_t		monitor;
}	t_table;


//parse_args.c
int			parse_args(int argc, char **argv, t_table *table);

//utils.c
long int	ft_time(void);
long int	get_elapsed_time(t_table *table);
int			check_one_philo(t_table  *table);