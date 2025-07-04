/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/04 16:22:03 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int	init_table(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo)
		return (1);
	table->forks = malloc(sizeof(t_fork) * table->n_philo);
	if (!table->forks)
		return (1);
	
	return (0);
}

void	init_right_fork(t_table *table)
{
	int	i;
	
	i = 0;
	while (i < table->n_philo)
	{
		if (i < table->n_philo - 1)
			table->philo[i].right_fork = table->philo[i + 1].left_fork;
		else if (i == table->n_philo - 1)
			table->philo[i].right_fork = table->philo[0].left_fork;
		i++;
	}
}

void	init_fork_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_init(&table->philo[i].left_fork->m_fork, NULL);
		i++;
	}
}

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].table = table;
		table->philo[i].left_fork = malloc(sizeof(t_fork));
		table->philo[i].left_fork->fork_id = i + 1;
		table->philo[i].died = 0;
		table->philo[i].last_meal = get_elapsed_time(table);
		i++;
	}
	init_right_fork(table);
	init_fork_mutex(table);
	return (0);
}

int	is_even(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (1);
	else
		return (0);
}

void	eat_routine(t_philo *philo)
{
	if (is_even(philo))
	{
		philo->last_meal = get_elapsed_time(philo->table);
		pthread_mutex_lock(&philo->left_fork->m_fork);
		printf("%ld %i has taken left fork %i\n", get_elapsed_time(philo->table), philo->id, philo->left_fork->fork_id);
		pthread_mutex_lock(&philo->right_fork->m_fork);
		printf("%ld %i has taken right fork %i\n", get_elapsed_time(philo->table), philo->id, philo->right_fork->fork_id);
		printf("%ld %i is eating\n", get_elapsed_time(philo->table), philo->id);
		usleep(philo->table->time_eat * 1000);
		philo->last_meal = 0;
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->left_fork->m_fork);
		pthread_mutex_unlock(&philo->right_fork->m_fork);
	}
	else
	{
		philo->last_meal = get_elapsed_time(philo->table);
		pthread_mutex_lock(&philo->right_fork->m_fork);
		printf("%ld %i has taken right fork %i\n", get_elapsed_time(philo->table), philo->id, philo->right_fork->fork_id);
		pthread_mutex_lock(&philo->left_fork->m_fork);
		printf("%ld %i has taken left fork %i\n", get_elapsed_time(philo->table), philo->id, philo->left_fork->fork_id);
		printf("%ld %i is eating\n", get_elapsed_time(philo->table), philo->id);
		usleep(philo->table->time_eat * 1000);
		//mutex for last eat;
		philo->last_meal = 0;
		//mutext for meals eaten
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->right_fork->m_fork);
		pthread_mutex_unlock(&philo->left_fork->m_fork);
	}
}

// int	check_death(t_philo *philo)
// {
// 	if (philo->last_eat > philo->table->time_die)
// 	{
// 		philo->died = 1;
// 		printf("%ld %i died\n", get_elapsed_time(philo->table), philo->id);
// 		return (1);
// 	}
// 	return (0);
// }

int	*philo_routine(void *philo_arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)philo_arg;
	while (1)
	{
		eat_routine(philo);
		printf("%ld %i is sleeping\n", get_elapsed_time(philo->table), philo->id);
		usleep(philo->table->time_sleep * 1000);
		printf("%ld %i is thinking\n", get_elapsed_time(philo->table), philo->id);
	}
	return (0);
}

int	*monitor_routine(void *table_arg)
{
	t_table	*table;
	
	table = (t_table *)table_arg;
	
}

int	start_simulation(t_table *table)
{
	int	i;
	
	i = 0;
	pthread_create(table->monitor, NULL, monitor_routine, table);
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, philo_routine, &table->philo[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	return (0);
}



int	main(int argc, char **argv)
{
	t_table	table;
	//int i = 0;

	if (parse_args(argc, argv, &table) != 0)
		return (1);
	if (init_table(&table))
		return (1);
	if (init_philos(&table))
		return (1);
	if (check_one_philo(&table))
		return (0);
	start_simulation(&table);
	return (0);
}


