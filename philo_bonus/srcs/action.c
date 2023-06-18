/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:31:02 by dlu               #+#    #+#             */
/*   Updated: 2023/06/18 21:50:53 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Eating routine. */
static void	ft_eat(t_philo *philo)
{
	if (ft_gettime() - philo->last_meal < philo->eat_ms + philo->sleep_ms + 10)
		usleep(500);
	sem_wait(philo->data->fork);
	ft_log(philo, (t_act) FORK);
	sem_wait(philo->data->fork);
	ft_log(philo, (t_act) FORK);
	sem_wait(philo->meal);
	philo->last_meal = ft_gettime();
	philo->left_meal--;
	if (!philo->left_meal)
		philo->finished = 1;
	ft_log(philo, (t_act) EAT);
	usleep(philo->eat_ms * 1000);
	sem_post(philo->meal);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
}

/* Philosopher routine, until reached required meal. */
void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!philo->finished)
	{
		ft_log(philo, (t_act) THINK);
		ft_eat(philo);
		ft_log(philo, (t_act) SLEEP);
		usleep(philo->sleep_ms * 1000);
	}
	return (NULL);
}

/* Stand behind the philosopher to await their death. */
void	*ft_psychopomp(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (TRUE)
	{
		sem_wait(philo->meal);
		if (philo->left_meal
			&& ft_gettime() - philo->last_meal > philo->die_ms)
		{
			ft_log(philo, (t_act) DIED);
			sem_wait(philo->data->write);
			sem_post(philo->data->death);
			return (NULL);
		}
		sem_post(philo->meal);
	}
}
