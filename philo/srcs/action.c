/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:31:02 by dlu               #+#    #+#             */
/*   Updated: 2023/06/18 21:08:29 by dlu              ###   ########.fr       */
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
	if (!philo->left_meal)
		philo->finished = 1;
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
	if (!philo->left_meal)
		philo->finished = 1;
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
	pthread_mutex_lock(&philo->data->death);
	while (!philo->someone_died && !philo->finished)
	{
		if (philo->fork_l == philo->fork_r)
			break ;
		pthread_mutex_unlock(&philo->data->death);
		ft_log(philo, (t_act) THINK);
		if (philo->id % 2 == 0)
			ft_eat_even(philo);
		else
			ft_eat_odd(philo);
		ft_log(philo, (t_act) SLEEP);
		usleep(philo->sleep_ms * 1000);
		pthread_mutex_lock(&philo->data->death);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (NULL);
}

/* Stand behind the philosopher to await their death. */
void	*ft_psychopomp(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *) arg;
	while (TRUE)
	{
		pthread_mutex_lock(&philo->meal);
		if (philo->left_meal
			&& ft_gettime() - philo->last_meal > philo->die_ms)
		{
			ft_log(philo, (t_act) DIED);
			pthread_mutex_lock(&philo->data->death);
			i = -1;
			while (++i < philo->data->philo_nbr)
				philo->data->philos[i].someone_died = 1;
			pthread_mutex_unlock(&philo->data->death);
			pthread_mutex_unlock(&philo->meal);
			return (NULL);
		}
		else if (philo->finished)
			return (pthread_mutex_unlock(&philo->meal), NULL);
		pthread_mutex_unlock(&philo->meal);
	}
}
