/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller- <ekeller-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:40:56 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/27 20:22:53 by ekeller-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_monitor	*data;

	data = malloc(sizeof(t_monitor));
	if (parse_args(argc, argv, data) != 0)
		return (1);


	free(data);
	return (0);
}

