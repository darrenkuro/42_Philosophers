/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:30:01 by dlu               #+#    #+#             */
/*   Updated: 2023/06/18 00:19:04 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Initialize philosopher and mutexes. */
static void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < data->philo_nbr)
	{
		pthread_mutex_init(&data->philos[i].meal, NULL);
		data->philos[i].id = i + 1;
		data->philos[i].someone_died = 0;
		data->philos[i].finished = 0;
		data->philos[i].die_ms = data->die_ms;
		data->philos[i].sleep_ms = data->sleep_ms;
		data->philos[i].eat_ms = data->eat_ms;
		data->philos[i].left_meal = data->eat_time;
		data->philos[i].start_ts = ft_gettime();
		data->philos[i].last_meal = ft_gettime();
		data->philos[i].fork_r = &data->forks[i];
		data->philos[i].data = data;
		if (i > 0)
			data->philos[i].fork_l = &data->forks[i - 1];
	}
	if (data->philo_nbr)
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
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->death, NULL);
	init_philos(data);
	return (TRUE);
}

/* Free memory and destory mutexes before exit. */
static void	free_and_destory(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->philos[i].meal);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->death);
	free(data->philos);
	free(data->forks);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac != 5 && ac != 6)
		return (ft_perror(ERR_ARGNUM), EXIT_FAILURE);
	if (!init_data(ac, av, &data))
		return (ft_perror(ERR_ARGFMT), EXIT_FAILURE);
	if (data.philo_nbr == 0)
		return (free_and_destory(&data), EXIT_SUCCESS);
	i = -1;
	while (++i < data.philo_nbr)
		pthread_create(&data.philos[i].th, NULL, ft_routine, &data.philos[i]);
	i = -1;
	while (++i < data.philo_nbr)
		pthread_create(&data.philos[i].monitor_th, NULL, ft_psychopomp,
			&data.philos[i]);
	i = -1;
	while (++i < data.philo_nbr)
		pthread_join(data.philos[i].th, NULL);
	i = -1;
	while (++i < data.philo_nbr)
		pthread_join(data.philos[i].monitor_th, NULL);
	return (free_and_destory(&data), EXIT_SUCCESS);
}
