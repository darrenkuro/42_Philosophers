/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:30:01 by dlu               #+#    #+#             */
/*   Updated: 2023/06/18 20:54:05 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Kill processes, free memory and destory mutexes before exit. */
static void	free_and_destory(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		sem_close(data->philos[i].meal);
		sem_unlink(data->philos[i].sem_name);
	}
	sem_close(data->write);
	sem_close(data->fork);
	sem_close(data->end);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_END);
	free(data->philos);
}

/* Kill all child processes when receiving end semaphore. */
static void	*ft_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *) arg;
	sem_wait(data->end);
	i = -1;
	while (++i < data->philo_nbr)
		kill(data->philos[i].pid, SIGKILL);
	return (NULL);
}

/* Start the philosopher processes, return TRUE only if it's child process. */
static int	start_philos(t_data *data, int i)
{
	data->philos[i].pid = fork();
	if (data->philos[i].pid == 0)
	{
		pthread_create(&data->philos[i].monitor_th, NULL, ft_psychopomp,
			&data->philos[i]);
		pthread_detach(data->philos[i].monitor_th);
		ft_routine(&data->philos[i]);
		return (TRUE);
	}
	else
		return (FALSE);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac != 5 && ac != 6)
		return (ft_perror(ERR_ARGNUM), EXIT_FAILURE);
	if (!init_data(ac, av, &data))
		return (ft_perror(ERR_ARGFMT), EXIT_FAILURE);
	if (data.philo_nbr > MAX_PHILO)
		return (ft_perror(ERR_PHILO), EXIT_FAILURE);
	init_philos(&data);
	init_sems(&data);
	if (data.philo_nbr == 0 || data.eat_time == 0)
		return (free_and_destory(&data), EXIT_SUCCESS);
	i = -1;
	while (++i < data.philo_nbr)
		if (start_philos(&data, i))
			return (EXIT_SUCCESS);
	pthread_create(&data.monitor, NULL, ft_monitor, &data);
	pthread_detach(data.monitor);
	i = -1;
	while (++i < data.philo_nbr)
		waitpid(data.philos[i].pid, &data.philos[i].exit_status, 0);
	return (free_and_destory(&data), EXIT_SUCCESS);
}
