/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:58:49 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/04 12:08:11 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	ft_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

long int	get_elapsed_time(t_table *table)
{
	long int current_time;

	current_time = ft_time();
	return (current_time - table->start_time);
}

int	check_one_philo(t_table  *table)
{	
	if (table->n_philo == 1)
	{
		usleep(table->time_die * 1000);
		printf("%ld %i died\n", get_elapsed_time(table), table->philo->id);
		//free
		return (1);
	}
	return (0);
}