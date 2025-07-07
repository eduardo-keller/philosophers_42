/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:29:07 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/07 17:26:41 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_routine(t_philo *philo)
{
	if (is_even(philo))
	{
		pthread_mutex_lock(&philo->left_fork->m_fork);
		safe_print("has taken left fork", philo->table);
		pthread_mutex_lock(&philo->right_fork->m_fork);
		safe_print("has taken right fork", philo->table);
		pthread_mutex_lock(&philo->t_last_meal_mut);
		philo->t_last_meal = get_time();
		pthread_mutex_unlock(&philo->t_last_meal_mut);
		safe_print("is eating", philo->table);
		usleep(philo->table->time_eat * 1000);
		pthread_mutex_lock(&philo->meals_eaten_mut);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_eaten_mut);
		pthread_mutex_unlock(&philo->left_fork->m_fork);
		pthread_mutex_unlock(&philo->right_fork->m_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->m_fork);
		safe_print("has taken right fork", philo->table);
		pthread_mutex_lock(&philo->left_fork->m_fork);
		safe_print("has taken left fork", philo->table);
		pthread_mutex_lock(&philo->t_last_meal_mut);
		philo->t_last_meal = get_time();
		pthread_mutex_unlock(&philo->t_last_meal_mut);
		safe_print("is eating", philo->table);
		usleep(philo->table->time_eat * 1000);
		pthread_mutex_lock(&philo->meals_eaten_mut);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_eaten_mut);
		pthread_mutex_unlock(&philo->right_fork->m_fork);
		pthread_mutex_unlock(&philo->left_fork->m_fork);
	}
}

int	check_dead_flag(t_table *table)
{
	pthread_mutex_lock(&table->is_dead_mut);
	if (table->is_dead)
	{
		pthread_mutex_unlock(&table->is_dead_mut);
		return (1);
	}
	pthread_mutex_unlock(&table->is_dead_mut);	
	return (0);
}

void	*philo_routine(void *philo_arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)philo_arg;
	while (1)
	{
		
		if (check_dead_flag(philo->table))
			return (NULL);
		eat_routine(philo);
		if (check_dead_flag(philo->table))
			return (NULL);
		safe_print("is sleeping", philo->table);
		usleep(philo->table->time_sleep * 1000);
		if (check_dead_flag(philo->table))
			return (NULL);
		safe_print("is thinking", philo->table);
	}
	return (0);
}

