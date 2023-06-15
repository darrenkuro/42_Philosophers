/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:30:01 by dlu               #+#    #+#             */
/*   Updated: 2023/06/15 06:01:48 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Initialize philosopher and mutexes. */
static void	init_philo(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->write, NULL);
	//pthread_mutex_init(&data->death, NULL);
	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->philo_nbr)
	{
		pthread_mutex_init(&data->philos[i].meal, NULL);
		pthread_mutex_init(&data->philos[i].death, NULL);
		data->philos[i].id = i + 1;
		data->philos[i].eat_ms = data->eat_ms;
		data->philos[i].sleep_ms = data->sleep_ms;
		data->philos[i].someone_died = 0;
		data->philos[i].write = &data->write;
		data->philos[i].left_meal = data->eat_time;
		data->philos[i].start_ts = data->start_ts;
		data->philos[i].last_meal = ft_gettime();
		data->philos[i].fork_r = &data->forks[i];
		if (i > 0)
			data->philos[i].fork_l = &data->forks[i - 1];
	}
	data->philos[0].fork_l = &data->forks[data->philo_nbr - 1];
}

/* Initialize data with given args, return FALSE if any arg is invalid. */
static int	init_data(int ac, char **av, t_data *data)
{
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
	data->start_ts = ft_gettime();
	data->philo_done = 0;
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac != 5 && ac != 6)
		return (ft_perror(ERR_ARGNUM), EXIT_FAILURE);
	if (!init_data(ac, av, &data))
		return (ft_perror(ERR_ARGFMT), EXIT_FAILURE);
	if (data.philo_nbr == 0 || data.eat_time == 0)
		return (EXIT_SUCCESS);
	init_philo(&data);
	i = -1;
	while (++i < data.philo_nbr)
		pthread_create(&data.philos[i].th, NULL, ft_routine, &data.philos[i]);
	pthread_create(&data.psychopomp, NULL, ft_psychopomp, &data);
	i = -1;
	while (++i < data.philo_nbr)
		pthread_join(data.philos[i].th, NULL);
	pthread_join(data.psychopomp, NULL);
	return (EXIT_SUCCESS);
}
