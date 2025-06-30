/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:41:15 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/30 17:41:54 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_atoi(const char *nptr)
{
	int	result;

	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		printf ("arg must be positive\n");
		return (-1);
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + (*nptr - 48);
		nptr++;
	}
	return (result);
}

static int	is_numeric(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("numeric argument required\n");
				return (1);	
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void	init_struct(char **argv, t_table *monitor)
{
	monitor->n_philo = ft_atoi(argv[1]);
	monitor->time_die = ft_atoi(argv[2]);
	monitor->time_eat = ft_atoi(argv[3]);
	monitor->time_sleep = ft_atoi(argv[4]);
	monitor->start_time = ft_time();
	if (argv[5])
		monitor->n_eat = ft_atoi(argv[5]);
	else
		monitor->n_eat = -1;
	return ;
}

int	parse_args(int argc, char **argv, t_table *monitor)
{
	if (argc < 5 || argc > 6)
	{
		printf ("wrong number of arguments\n");
		printf ("args: n_philo, time_to_die, time_to_eat, time_to_sleep, n_eat(optional)\n");
		free(monitor);
		return (1);
	}
	if (is_numeric(argv) != 0)
	{
		free(monitor);
		return 1;
	}	
	init_struct(argv, monitor);
	return (0);
}