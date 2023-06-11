/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:30:01 by dlu               #+#    #+#             */
/*   Updated: 2023/06/11 21:31:25 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Initialize data with given args, return FALSE if any arg is invalid. */
static int	init_data(int ac, char **av, t_data *data)
{
	data->philo_nbr = ft_parse_arg(av[1]);
	data->die_ms = ft_parse_arg(av[2]);
	data->eat_ms = ft_parse_arg(av[3]);
	data->sleep_ms = ft_parse_arg(av[4]);
	if (data->philo_nbr == ERROR || data->die_ms == ERROR
		|| data->eat_ms == ERROR || data->sleep_ms == ERROR)
		return (FALSE);
	if (ac == 6 && ft_parse_arg(av[5]) != ERROR)
		data->eat_time = ft_parse_arg(av[5]);
	else if (ac == 6)
		return (FALSE);
	else
		data->eat_time = ERROR;
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (ft_perror(ERR_ARGNUM), EXIT_FAILURE);
	if (!init_data(ac, av, &data))
		return (ft_perror(ERR_ARGFMT), EXIT_FAILURE);
	if (data->philo_nbr == 0 || data->eat_time == 0)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
