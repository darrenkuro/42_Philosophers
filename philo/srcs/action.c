/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:31:02 by dlu               #+#    #+#             */
/*   Updated: 2023/06/16 11:06:36 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Eating routine for even number philosopher, left fork first. */
static void	ft_eat_even(t_philo *philo)
{
	if (ft_gettime() - philo->last_meal < philo->eat_ms + philo->sleep_ms + 10)
		usleep(500);
	pthread_mutex_lock(philo->fork_l);
	ft_log(philo, (t_act) FORK);
	pthread_mutex_lock(philo->fork_r);
	ft_log(philo, (t_act) FORK);
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = ft_gettime();
	philo->left_meal--;
	ft_log(philo, (t_act) EAT);
	usleep(philo->eat_ms * 1000);
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

/* Eating routine for odd number philosopher, right fork first. */
static void	ft_eat_odd(t_philo *philo)
{
	if (ft_gettime() - philo->last_meal < philo->eat_ms + philo->sleep_ms + 10)
		usleep(500);
	pthread_mutex_lock(philo->fork_r);
	ft_log(philo, (t_act) FORK);
	pthread_mutex_lock(philo->fork_l);
	ft_log(philo, (t_act) FORK);
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = ft_gettime();
	philo->left_meal--;
	ft_log(philo, (t_act) EAT);
	usleep(philo->eat_ms * 1000);
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

/* Philosopher routine, until reached required meal or someone died. */
void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		usleep(500);
	pthread_mutex_lock(philo->death);
	while (!philo->someone_died)
	{
		pthread_mutex_unlock(philo->death);
		ft_log(philo, (t_act) THINK);
		if (philo->id % 2 == 0)
			ft_eat_even(philo);
		else
			ft_eat_odd(philo);
		ft_log(philo, (t_act) SLEEP);
		usleep(philo->sleep_ms * 1000);
		pthread_mutex_lock(philo->death);
		//usleep(500);
	}
	printf("%d has returned\n", philo->id);
	pthread_mutex_unlock(philo->death);
	return (NULL);
}

void	*ft_psychopomp(void *arg)
{
	t_data *data;
	int		i;
	int		j;

	data = (t_data *) arg;
	while (TRUE)
	{
		i = -1;
		data->philo_done = 0;
		while (++i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->philos[i].meal);
			if (data->philos[i].left_meal
				&& ft_gettime() - data->philos[i].last_meal > data->die_ms)
			{
				ft_log(&data->philos[i], (t_act) DIED);
				pthread_mutex_lock(&data->death);
				j = -1;
				while (++j < data->philo_nbr)
				{
					//pthread_mutex_lock(&data->philos[i].death);
					data->philos[j].someone_died = 1;
					//pthread_mutex_unlock(&data->philos[i].death);
				}
				pthread_mutex_unlock(&data->philos[i].meal);
				pthread_mutex_unlock(&data->death);
				return (NULL);
			}
			if (!data->philos[i].left_meal)
				data->philo_done++;
			pthread_mutex_unlock(&data->philos[i].meal);
		}
		if (data->philo_done == data->philo_nbr)
			return (NULL);
		usleep(500);
	}
}
