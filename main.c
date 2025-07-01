/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/07/01 13:42:40 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void	*philo_routine(t_table *table, t_philo *philo)
// {
// 	int	i;

// 	i = 1;
// 	while (i <= table->n_philo)
// 	{
// 		printf("im philo: %i\n", i);
// 		i++;
// 	}
// }

// void	start_simulation(t_table *table, t_philo *philo)
// {
// 	int	i;
// 	pthread_t	*philo;
	
// 	i = 0;
// 	while (i < table->n_philo)
// 	{
// 		pthread_create(philo[i], NULL, philo_routine(table, philo), )
// 	}
// }

int	init_table(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo)
		return (1);
	
	return (0);
}

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philo[i].id = i;
		table->philo[i].meals_eaten = 0;
		table->philo[i].table = table;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		i = 1;


	if (parse_args(argc, argv, &table) != 0)
		return (1);
	if (init_table(&table))
		return (1);
	if (init_philos(&table))
		return (1);
	while(i <= table.n_philo)
		printf("philo id: %i\n", i++);
	usleep(1000000);
	printf("sleep time: %ld\n", get_elapsed_time(&table));
	return (0);
}
