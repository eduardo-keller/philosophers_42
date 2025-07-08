/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:29:07 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/08 17:18:07 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat_routine(t_philo *philo)
{
	//if (is_even(philo))
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->m_fork);
		safe_print("has taken left fork", philo);
		pthread_mutex_lock(&philo->right_fork->m_fork);
		safe_print("has taken right fork", philo);
		pthread_mutex_lock(&philo->t_last_meal_mut);
		philo->t_last_meal = get_time();
		pthread_mutex_unlock(&philo->t_last_meal_mut);
		safe_print("is eating", philo);
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
		safe_print("has taken right fork", philo);
		pthread_mutex_lock(&philo->left_fork->m_fork);
		safe_print("has taken left fork", philo);
		pthread_mutex_lock(&philo->t_last_meal_mut);
		philo->t_last_meal = get_time();
		pthread_mutex_unlock(&philo->t_last_meal_mut);
		safe_print("is eating", philo);
		usleep(philo->table->time_eat * 1000);
		pthread_mutex_lock(&philo->meals_eaten_mut);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_eaten_mut);
		pthread_mutex_unlock(&philo->left_fork->m_fork);
		pthread_mutex_unlock(&philo->right_fork->m_fork);
	}
}

// void	eat_routine(t_philo *philo)
// {
// 	t_fork	*first_fork;
// 	t_fork	*second_fork;
	
// 	if (philo->id == philo->table->n_philo)
// 	{
// 		first_fork = philo->right_fork;
// 		second_fork = philo->left_fork;
// 	}
// 	else
// 	{
// 		first_fork = philo->left_fork;
// 		second_fork = philo->right_fork;
// 	}
// 	pthread_mutex_lock(&first_fork->m_fork);
// 	safe_print("has taken a fork", philo);
// 	pthread_mutex_lock(&second_fork->m_fork);
// 	safe_print("has taken a fork", philo);
// 	pthread_mutex_lock(&philo->t_last_meal_mut);
// 	philo->t_last_meal = get_time();
// 	pthread_mutex_unlock(&philo->t_last_meal_mut);
// 	safe_print("is eating", philo);
// 	usleep(philo->table->time_eat * 1000);
// 	pthread_mutex_lock(&philo->meals_eaten_mut);
// 	philo->meals_eaten++;
// 	pthread_mutex_unlock(&philo->meals_eaten_mut);
// 	pthread_mutex_unlock(&first_fork->m_fork);
// 	pthread_mutex_unlock(&second_fork->m_fork);
// }


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
		safe_print("is sleeping", philo);
		usleep(philo->table->time_sleep * 1000);
		if (check_dead_flag(philo->table))
			return (NULL);
		safe_print("is thinking", philo);
	}
	return (NULL);
}

