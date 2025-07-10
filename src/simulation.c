/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:29:07 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/10 15:26:16 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->m_fork);
	safe_print("has taken a fork", philo);
	pthread_mutex_lock(&philo->right_fork->m_fork);
	safe_print("has taken a fork", philo);
	pthread_mutex_lock(&philo->t_last_meal_mut);
	philo->t_last_meal = get_time();
	pthread_mutex_unlock(&philo->t_last_meal_mut);
	pthread_mutex_lock(&philo->meals_eaten_mut);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mut);
	safe_print("is eating", philo);
	precise_sleep(philo->table->time_eat, philo->table);
	pthread_mutex_unlock(&philo->right_fork->m_fork);
	pthread_mutex_unlock(&philo->left_fork->m_fork);
}

void	*philo_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	if (philo->table->n_philo == 1)
	{
		safe_print("has take a fork", philo);
		return (NULL);
	}
	while (1)
	{
		if (check_end_simulation(philo->table))
			return (NULL);
		eat_routine(philo);
		if (check_end_simulation(philo->table))
			return (NULL);
		safe_print("is sleeping", philo);
		precise_sleep(philo->table->time_sleep, philo->table);
		if (check_end_simulation(philo->table))
			return (NULL);
		safe_print("is thinking", philo);
	}
	return (NULL);
}

int	check_n_meals(t_table *table, int *i)
{
	if (table->n_meal == -1)
		return (0);
	pthread_mutex_lock(&table->philo[*i].meals_eaten_mut);
	if (table->philo[*i].meals_eaten >= table->n_meal
		&& !table->philo[*i].is_full)
	{
		pthread_mutex_unlock(&table->philo[*i].meals_eaten_mut);
		table->philo[*i].is_full = 1;
		table->n_philo_full += 1;
		if (table->n_philo_full == table->n_philo)
		{
			pthread_mutex_lock(&table->end_simulation_mut);
			table->end_simulation = 1;
			pthread_mutex_unlock(&table->end_simulation_mut);
			return (1);
		}	
		return (0);
	}
	pthread_mutex_unlock(&table->philo[*i].meals_eaten_mut);
	return (0);
}

static void	death(t_table *table, int *i)
{
	pthread_mutex_unlock(&table->philo[*i].t_last_meal_mut);
	safe_print("died", &table->philo[*i]);
	pthread_mutex_lock(&table->end_simulation_mut);
	table->end_simulation = 1;
	pthread_mutex_unlock(&table->end_simulation_mut);
}

void	*monitor_routine(void *table_arg)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)table_arg;
	while (1)
	{
		if (check_end_simulation(table))
			return (NULL);
		pthread_mutex_lock(&table->philo[i].t_last_meal_mut);
		if (get_time() - table->philo[i].t_last_meal > table->time_die)
		{
			death(table, &i);
			return (NULL);
		}
		pthread_mutex_unlock(&table->philo[i].t_last_meal_mut);
		if (check_n_meals(table, &i))
			return (NULL);
		i = (i + 1) % table->n_philo;
		usleep(1000);
	}
	return (0);
}
