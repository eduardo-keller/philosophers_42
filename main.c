/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/07 18:23:44 by ekeller-@st      ###   ########.fr       */
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
	table->is_dead = 0;
	
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
		table->philo[i].t_last_meal = table->start_time;
		i++;
	}
	init_right_fork(table);
	return (0);
}

void	*monitor_routine(void *table_arg)
{
	t_table	*table;
	int		i;
	
	i = 0;
	table = (t_table *)table_arg;
	while(1)
	{
		if (check_dead_flag(table))
			return (NULL);
		pthread_mutex_lock(&table->philo[i].t_last_meal_mut);
		if (get_time() - table->philo[i].t_last_meal > table->time_die)
		{
			pthread_mutex_unlock(&table->philo[i].t_last_meal_mut);
			pthread_mutex_lock(&table->is_dead_mut);
			table->is_dead = 1;
			pthread_mutex_unlock(&table->is_dead_mut);

		}
		pthread_mutex_unlock(&table->philo[i].t_last_meal_mut);
		i = (i + 1) % table->n_philo;
		usleep(1000);
	}
	return (0);
}

int	start_simulation(t_table *table)
{
	int	i;
	
	i = 0;

	pthread_create(&table->monitor, NULL, monitor_routine, table);
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, philo_routine, &table->philo[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
		return (1);
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
	if (init_mutex(&table))
		return (1);
	
	start_simulation(&table);
	return (0);
}


