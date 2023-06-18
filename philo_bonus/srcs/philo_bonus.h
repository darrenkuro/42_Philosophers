/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:37:09 by dlu               #+#    #+#             */
/*   Updated: 2023/06/18 20:37:46 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <string.h>
# include <pthread.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

# define TRUE		1
# define FALSE		0
# define ERROR		-1
# define STDERR		2
# define ALIGN		0
# define MAX_PHILO	200
# define ERR_ARGNUM	"Error: Wrong number of arguments (should be 4 or 5).\n"
# define ERR_ARGFMT	"Error: Only numeric, non-negative, int range args.\n"
# define ERR_PHILO	"Error: Too many philosophers, max: 200.\n"
# define SEM_END	"/end"
# define SEM_FORK	"/fork"
# define SEM_WRITE	"/write"

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
	char	sem_name[6];
	pid_t	pid;
	t_pth	monitor_th;
	int		id;
	int		die_ms;
	int		eat_ms;
	int		sleep_ms;
	int		left_meal;
	int		finished;
	int		exit_status;
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
	t_pth	monitor;
	sem_t	*fork;
	sem_t	*write;
	sem_t	*end;
}	t_data;

int		ft_strlen(const char *str);
int		ft_parse_arg(const char *arg);
int		init_data(int ac, char **av, t_data *data);
void	init_sems(t_data *data);
void	init_philos(t_data *data);
void	ft_perror(const char *msg);
void	ft_log(t_philo *philo, t_act act);
void	*ft_routine(void *arg);
void	*ft_psychopomp(void *arg);
t_ll	ft_gettime(void);

#endif
