/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:17:38 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/07 15:42:32 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_fork_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_init(&table->philo[i].left_fork->m_fork, NULL);
		i++;
	}
}

static void	init_meals_eaten_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_init(&table->philo[i].meals_eaten_mut, NULL);
		i++;
	}
}

static void	init_last_meal_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_init(&table->philo[i].t_last_meal_mut, NULL);
		i++;
	}
}


int	init_mutex(t_table *table)
{
	//philo
	init_fork_mutex(table);
	init_meals_eaten_mutex(table);
	init_last_meal_mutex(table);
	
	//table
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->is_dead_mut, NULL);
	return (0);
}



//