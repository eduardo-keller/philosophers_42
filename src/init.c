/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:58:59 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/08 17:14:09 by ekeller-@st      ###   ########.fr       */
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

// static void	init_right_fork(t_table *table)
// {
// 	int	i;
	
// 	i = 0;
// 	while (i < table->n_philo)
// 	{
// 		if (i < table->n_philo - 1)
// 			table->philo[i].right_fork = table->philo[i + 1].left_fork;
// 		else if (i == table->n_philo - 1)
// 			table->philo[i].right_fork = table->philo[0].left_fork;
// 		i++;
// 	}
// }


int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].table = table;
		table->philo[i].left_fork = &table->forks[i];
		//table->philo[i].left_fork->fork_id = i + 1;
		table->philo[i].right_fork = &table->forks[(i + 1) % table->n_eat];
		table->philo[i].t_last_meal = table->start_time;
		i++;
	}
	//init_right_fork(table);
	return (0);
}


// int	init_philos(t_table *table)
// {
// 	int	i;
// 	t_fork	*fork_nbr;

// 	i = 0;
// 	while (i < table->n_philo)
// 	{
// 		fork_nbr = &table->forks[(i + 1) % table->n_philo];
// 		table->philo[i].id = i + 1;
// 		table->philo[i].meals_eaten = 0;
// 		table->philo[i].table = table;
// 		table->philo[i].left_fork = &table->forks[i];
// 		table->philo[i].left_fork->fork_id = i + 1;
// 		table->philo[i].right_fork = fork_nbr;
// 		table->philo[i].t_last_meal = table->start_time;
// 		if (table->philo[i].id % 2 == 0)
// 		{
// 			table->philo[i].left_fork = fork_nbr;
// 			table->philo[i].right_fork = &table->forks[i];
// 		}
// 		i++;
// 	}
// 	//init_right_fork(table);
// 	return (0);
// }