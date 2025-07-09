/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:17:38 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/09 15:52:57 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_fork_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_init(&table->forks[i].m_fork, NULL);
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

void	init_mutex(t_table *table)
{
	init_fork_mutex(table);
	init_meals_eaten_mutex(table);
	init_last_meal_mutex(table);
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->end_simulation_mut, NULL);
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->forks[i].m_fork);
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->philo[i].meals_eaten_mut);
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->philo[i].t_last_meal_mut);
		i++;
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->end_simulation_mut);
}
