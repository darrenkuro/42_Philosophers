/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:37:09 by dlu               #+#    #+#             */
/*   Updated: 2023/06/13 19:46:32 by dlu              ###   ########.fr       */
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
# define ALIGN		6
# define ERR_ARGNUM	"Error: Wrong number of arguments (should be 4 or 5).\n"
# define ERR_ARGFMT	"Error: Only numeric, non-negative, int range args.\n"

typedef long long		t_ll;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_pth;

typedef enum e_act
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED
}	t_act;

typedef struct s_philo
{
	t_mutex	*fork_l;
	t_mutex	*fork_r;
	t_pth	th;
	int		id;
	int		ate_time;
	t_ll	last_meal;
}	t_philo;

typedef struct s_data
{
	int		philo_nbr;
	int		die_ms;
	int		eat_ms;
	int		sleep_ms;
	int		eat_time;
	t_ll	start_ts;
	t_philo	*philos;
	t_mutex	*forks;
}	t_data;

void	ft_perror(const char *msg);
int		ft_strlen(const char *str);
int		ft_parse_arg(const char *arg);
void	ft_log(int ms, int id, t_act act);
t_ll	ft_gettime(void);

#endif
