/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:24:04 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/14 19:24:45 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# define TRUE 1
# define FALSE 0

# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;36m"
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
	struct s_pars	*game;
	bool			alive;
}	t_philo;

typedef struct s_pars
{
	sem_t	*printf_sem;
	sem_t	*meal_sem;
	sem_t	*alive_sem;
	sem_t	*dead_sem;
	sem_t	*time_sem;
	sem_t	*fork;
	sem_t	*all_eat;
	sem_t	*one_dead;
	int		nb_philo;
	int		total_meal;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		time;
	int		*pid;
	bool	dead;
	t_philo	*philo;
}	t_pars;

void		print_error(char *color, char *message);
void		wait_pid(t_pars *game);
void		init_game(t_pars *game, int argc, char **argv);
void		init_philo(int i, t_philo *philo, struct s_pars *game);
void		ft_usleep(int time, t_philo *philo);
void		print_philo(t_philo *philo, char *color, char *message);
void		free_philo(t_pars *game);
void		routine(t_philo *philo);
void		init_prog(t_pars *game, int argc, char **argv);
int			pars_arg(int argc, char **argv);
long long	ft_atoll(const char *nptr);
int			get_time(void);

#endif
