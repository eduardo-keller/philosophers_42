/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/26 18:58:45 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + (*nptr - 48);
		nptr++;
	}
	return (result * sign);
}

int	parse_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf ("wrong number of arguments\n");
		printf ("args: n_philo, time_to_die, \
			time_to_eat, time_to_sleep, n_eat(optional)\n");
		return (1);
	}
}

int	main(int argc, char **argv)
{
	if (parse_args(argc, argv) != 0)
		return (1);
}

