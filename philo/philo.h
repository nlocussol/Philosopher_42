/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:24:04 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/12 19:23:02 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0

# define RED "\033[0;31m"
# define GRAY "\033[0;37m"
# define BLUE "\e[38;5;191m"
# define GREEN "\033[0;32m"
# define PINK "\e[38;5;25m"

# define FORK_R "has taken a fork\n"
# define FORK_L "has taken a fork\n"
# define EATING "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIED "died\n"

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				nb_meal;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	struct s_pars	*game;
	bool			alive;
}	t_philo;

typedef struct s_pars
{
	pthread_mutex_t	printf;
	pthread_mutex_t	meal_m;
	pthread_mutex_t	nb_meal_m;
	pthread_mutex_t	last_meal_m;
	pthread_mutex_t	alive_m;
	pthread_mutex_t	dead_m;
	pthread_mutex_t	time_m;
	t_philo			*philo;
	int				nb_philo;
	int				total_meal;
	int				meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time;
	bool			dead;
}	t_pars;

void		ft_usleep(int time, t_philo *philo);
void		print_philo(t_philo *philo, char *color, char *message);
void		free_philo(t_pars *game);
void		join_thread(t_pars *game, pthread_t *thread);
void		*routine(void *philo);
void		init_prog(t_pars *game, int argc, char **argv);
int			pars_arg(int argc, char **argv);
long long	ft_atoll(const char *nptr);
int			get_time(void);

#endif
