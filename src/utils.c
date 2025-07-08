/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:58:49 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/08 17:16:19 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long long int get_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

unsigned long long int	get_elapsed_time(t_table *table)
{
	unsigned long long int current_time;

	current_time = get_time();
	return (current_time - table->start_time);
}

int	check_one_philo(t_table  *table)
{	
	if (table->n_philo == 1)
	{
		usleep(table->time_die * 1000);
		safe_print("died", &table->philo[0]);
		//free
		return (1);
	}
	return (0);
}

// int	is_even(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 		return (1);
// 	else
// 		return (0);
// }

void	safe_print(char *str, t_philo *philo)
{
	unsigned long long	time;
	
	pthread_mutex_lock(&philo->table->is_dead_mut);
	if (philo->table->is_dead)
	{
		pthread_mutex_unlock(&philo->table->is_dead_mut);
		return ;
	}
	pthread_mutex_unlock(&philo->table->is_dead_mut);
	time = get_elapsed_time(philo->table);
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%lld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->write_mutex);
}