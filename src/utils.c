/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:58:49 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/10 15:24:32 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long long int	get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

unsigned long long int	get_elapsed_time(t_table *table)
{
	unsigned long long int	current_time;

	current_time = get_time();
	return (current_time - table->start_time);
}


void	safe_print(char *str, t_philo *philo)
{
	unsigned long long	time;

	pthread_mutex_lock(&philo->table->end_simulation_mut);
	if (philo->table->end_simulation)
	{
		pthread_mutex_unlock(&philo->table->end_simulation_mut);
		return ;
	}
	pthread_mutex_unlock(&philo->table->end_simulation_mut);
	time = get_elapsed_time(philo->table);
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%lld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

int	check_end_simulation(t_table *table)
{
	pthread_mutex_lock(&table->end_simulation_mut);
	if (table->end_simulation)
	{
		pthread_mutex_unlock(&table->end_simulation_mut);
		return (1);
	}
	pthread_mutex_unlock(&table->end_simulation_mut);
	return (0);
}
