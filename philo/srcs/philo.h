/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:37:09 by dlu               #+#    #+#             */
/*   Updated: 2023/06/11 21:27:48 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

# define TRUE		1
# define FALSE		0
# define ERROR		-1
# define STDERR		2
# define ERR_ARGNUM	"Error: Wrong number of arguments (should be 4 or 5).\n"
# define ERR_ARGFMT	"Error: Only numeric, non-negative, int range args.\n"

typedef struct s_data
{
	int	philo_nbr;
	int	die_ms;
	int	eat_ms;
	int	sleep_ms;
	int	eat_time;
}	t_data;

void	ft_perror(const char *msg);
int		ft_strlen(const char *str);
int		ft_parse_arg(const char *arg);

#endif
