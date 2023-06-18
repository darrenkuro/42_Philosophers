/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:37:09 by dlu               #+#    #+#             */
/*   Updated: 2023/06/18 12:06:39 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <semaphore.h>
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
typedef unsigned int	t_ui;
typedef pthread_t		t_pth;
typedef struct s_data	t_data;

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
	sem_t	*meal;
	pid_t	pid;
	t_pth	monitor_th;
	int		id;
	int		die_ms;
	int		eat_ms;
	int		sleep_ms;
	int		left_meal;
	int		someone_died;
	int		finished;
	t_ll	last_meal;
	t_ll	start_ts;
	t_data	*data;
}	t_philo;

typedef struct s_data
{
	int		philo_nbr;
	int		die_ms;
	int		eat_ms;
	int		sleep_ms;
	int		eat_time;
	t_philo	*philos;
	sem_t	*forks;
	sem_t	*write;
	sem_t	*death;
}	t_data;

void	ft_perror(const char *msg);
int		ft_strlen(const char *str);
int		ft_parse_arg(const char *arg);
void	ft_log(t_philo *philo, t_act act);
void	*ft_routine(void *arg);
void	*ft_psychopomp(void *arg);
t_ll	ft_gettime(void);

#endif
