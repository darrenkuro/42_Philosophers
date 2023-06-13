/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:52:05 by dlu               #+#    #+#             */
/*   Updated: 2023/06/12 19:44:58 by dlu              ###   ########.fr       */
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
void	ft_log(int ms, int id, t_act act)
{
	if (act == FORK)
		printf("%*d %d has taken a fork\n", ALIGN, ms, id);
	if (act == EAT)
		printf("%*d %d is eating\n", ALIGN, ms, id);
	if (act == SLEEP)
		printf("%*d %d is sleeping\n", ALIGN, ms, id);
	if (act == THINK)
		printf("%*d %d is thinking\n", ALIGN, ms, id);
	if (act == DIED)
		printf("%*d %d has died\n", ALIGN, ms, id);
}

/* Get the current time in ms. */
t_ll	ft_gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
