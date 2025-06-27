/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:41 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/27 20:19:49 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <limits.h> //INT_MAX
# include <pthread.h> // mutex: init, destroy, lock, unlock
					// threads: create, join, detach

typedef struct s_monitor
{
	int	n_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	n_eat;
}	t_monitor;


int	parse_args(int argc, char **argv, t_monitor *data);