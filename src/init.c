/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:58:59 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/10 15:51:26 by ekeller-@st      ###   ########.fr       */
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
	{
		free(table->philo);
		return (1);
	}	
	table->end_simulation = 0;
	table->n_philo_full = 0;
	return (0);
}

int	init_philos(t_table *table)
{
	int		i;
	t_fork	*fork_next;

	i = 0;
	while (i < table->n_philo)
	{
		fork_next = &table->forks[(i + 1) % table->n_philo];
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].is_full = 0;
		table->philo[i].table = table;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].left_fork->fork_id = i + 1;
		table->philo[i].right_fork = fork_next;
		table->philo[i].t_last_meal = table->start_time;
		if (table->philo[i].id % 2 == 0)
		{
			table->philo[i].left_fork = fork_next;
			table->philo[i].right_fork = &table->forks[i];
		}
		i++;
	}
	return (0);
}

void	precise_sleep(long time, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		if (elapsed >= time)
			break ;
		remaining = time - elapsed;
		if (remaining > 5)
			usleep(remaining * 500);
		else
			usleep(100);
		if (check_end_simulation(table))
			break ;
	}
}
