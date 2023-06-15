/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:52:05 by dlu               #+#    #+#             */
/*   Updated: 2023/06/15 03:43:37 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Return the length of the string. */
int	ft_strlen(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

/* Print given message to strerr. */
void	ft_perror(const char *msg)
{
	write(STDERR, msg, ft_strlen(msg));
}

/* Attempt to parse arg, return -1 if arg is invalid. */
int	ft_parse_arg(const char *arg)
{
	long long	ret;

	ret = 0;
	if (*arg == '+')
		++arg;
	while (*arg)
	{
		if (*arg >= '0' && *arg <= '9')
			ret = ret * 10 + (*arg - '0');
		else
			return (ERROR);
		++arg;
	}
	if (ret <= INT_MAX)
		return ((int) ret);
	else
		return (ERROR);
}

/* Log the activity. */
void	ft_log(t_philo *philo, t_act act)
{
	t_ll	ms;

	pthread_mutex_lock(philo->write);
	ms = ft_gettime() - philo->start_ts;
	if (act == FORK)
		printf("%*lld %d has taken a fork\n", ALIGN, ms, philo->id);
	if (act == EAT)
		printf("%*lld %d is eating\n", ALIGN, ms, philo->id);
	if (act == SLEEP)
		printf("%*lld %d is sleeping\n", ALIGN, ms, philo->id);
	if (act == THINK)
		printf("%*lld %d is thinking\n", ALIGN, ms, philo->id);
	if (act == DIED)
		printf("%*lld %d has died\n", ALIGN, ms, philo->id);
	pthread_mutex_unlock(philo->write);
}

/* Get the current time in ms. */
t_ll	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
