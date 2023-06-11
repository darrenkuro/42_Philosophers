/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:52:05 by dlu               #+#    #+#             */
/*   Updated: 2023/06/11 21:22:51 by dlu              ###   ########.fr       */
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
