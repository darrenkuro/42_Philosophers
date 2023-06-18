/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:01:18 by dlu               #+#    #+#             */
/*   Updated: 2023/06/18 21:04:56 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Initialize semaphores. */
void	init_sems(t_data *data)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_END);
	data->fork = sem_open(SEM_FORK, O_CREAT | O_EXCL, 0700, data->philo_nbr);
	data->write = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0700, 1);
	data->end = sem_open(SEM_END, O_CREAT | O_EXCL, 0700, 0);
}

/* Initialize philosophers. */
void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		data->philos[i].sem_name[0] = '/';
		data->philos[i].sem_name[1] = 'M';
		data->philos[i].sem_name[2] = i / 100 + '0';
		data->philos[i].sem_name[3] = (i % 100) / 10 + '0';
		data->philos[i].sem_name[4] = (i % 10) + '0';
		data->philos[i].sem_name[5] = '\0';
		sem_unlink(data->philos[i].sem_name);
		data->philos[i].meal = sem_open(data->philos[i].sem_name, \
			O_CREAT | O_EXCL, 0700, 1);
		data->philos[i].id = i + 1;
		data->philos[i].pid = 0;
		data->philos[i].finished = 0;
		data->philos[i].die_ms = data->die_ms;
		data->philos[i].sleep_ms = data->sleep_ms;
		data->philos[i].eat_ms = data->eat_ms;
		data->philos[i].left_meal = data->eat_time;
		data->philos[i].start_ts = ft_gettime();
		data->philos[i].last_meal = ft_gettime();
		data->philos[i].data = data;
	}
}

/* Initialize data with given args, return FALSE if any arg is invalid. */
int	init_data(int ac, char **av, t_data *data)
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
	return (TRUE);
}
