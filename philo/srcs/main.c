/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:30:01 by dlu               #+#    #+#             */
/*   Updated: 2023/06/14 11:34:33 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Initialize philosopher and create the threads. */
static int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_ms = data->eat_ms;
		data->philos[i].sleep_ms = data->sleep_ms;
		data->philos[i].fork_r = data->forks[i];
		if (i > 0)
			data->philos[i].fork_l = data->forks[i - 1];
	}
	data->philos[0].fork_l = data->forks[data->philo_nbr - 1];
}

/* Initialize data with given args, return FALSE if any arg is invalid. */
static int	init_data(int ac, char **av, t_data *data)
{
	int	i;

	data->eat_time = ERROR;
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
	data->philos = (t_philo *) malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (FALSE);
	data->forks = (t_mutex *) malloc(sizeof(t_mutex) * data->philo_nbr);
	if (!data->forks)
		return (free(data->philos), FALSE);
	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_init(data->forks[i], NULL);
	data->start_ts = ft_gettime();
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (ft_perror(ERR_ARGNUM), EXIT_FAILURE);
	if (!init_data(ac, av, &data))
		return (ft_perror(ERR_ARGFMT), EXIT_FAILURE);
	if (data.philo_nbr == 0 || data.eat_time == 0)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
