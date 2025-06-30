/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:41 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/30 18:58:31 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <limits.h> //INT_MAX
# include <pthread.h> // mutex: init, destroy, lock, unlock
					// threads: create, join, detach

typedef struct s_table
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
	unsigned long	start_time;
}	t_table;


typedef struct s_philo
{
	pthread_t	thread;
}	t_philo;

int			parse_args(int argc, char **argv, t_table *monitor);
long int	ft_time(void);
long int	get_elapsed_time(t_table *monitor);