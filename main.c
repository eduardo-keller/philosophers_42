/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/10 15:27:27 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	pthread_create(&table->monitor, NULL, monitor_routine, table);
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				philo_routine, &table->philo[i]))
			return (1);
		i++;
	}
	if (pthread_join(table->monitor, NULL) != 0)
		return (1);
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	int i = 0;
	if (parse_args(argc, argv, &table) != 0)
		return (1);
	if (init_table(&table))
		return (1);
	if (init_philos(&table))
		return (1);
	init_mutex(&table);
	start_simulation(&table);
	while (i < table.n_philo)
	{
		printf("philo %i ate %i times\n", table.philo[i].id, table.philo[i].meals_eaten);
		i++;
	}
	destroy_mutex(&table);
	free(table.forks);
	free(table.philo);
	return (0);
}
