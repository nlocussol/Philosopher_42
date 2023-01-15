/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:38:56 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/15 11:34:44 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time(void)
{
	struct timeval	tv_s;
	struct timezone	tv_u;
	int				time;

	gettimeofday(&tv_s, &tv_u);
	time = tv_s.tv_usec / 1000 + ((tv_s.tv_sec % 1000) * 1000);
	return (time);
}

void	init_philo(int i, t_philo *philo, t_pars *game)
{
	philo->id = i + 1;
	philo->last_meal = get_time();
	philo->nb_meal = 0;
	philo->alive = true;
	philo->game = game;
}

void	unlink_all(void)
{
	sem_unlink("printf_sem");
	sem_unlink("meal_sem");
	sem_unlink("alive_sem");
	sem_unlink("dead_sem");
	sem_unlink("time_sem");
	sem_unlink("fork_sem");
	sem_unlink("all_eat_sem");
	sem_unlink("one_dead_sem");
	sem_unlink("dead_print_sem");
}

void	init_game(t_pars *game, int argc, char **argv)
{
	game->nb_philo = ft_atoll(argv[1]);
	game->time_to_die = ft_atoll(argv[2]);
	game->time_to_eat = ft_atoll(argv[3]);
	game->time_to_sleep = ft_atoll(argv[4]);
	game->time = get_time();
	game->total_meal = -1;
	if (argc == 6)
		game->total_meal = ft_atoll(argv[5]);
	game->dead = false;
	game->pid = malloc(sizeof(int) * game->nb_philo);
	unlink_all();
	game->printf_sem = sem_open("printf_sem", O_CREAT, 0660, 1);
	game->meal_sem = sem_open("meal_sem", O_CREAT, 0660, 1);
	game->alive_sem = sem_open("alive_sem", O_CREAT, 0660, 1);
	game->dead_sem = sem_open("dead_sem", O_CREAT, 0660, 1);
	game->time_sem = sem_open("time_sem", O_CREAT, 0660, 1);
	game->all_eat = sem_open("all_eat_sem", O_CREAT, 0660, 0);
	game->fork = sem_open("fork_sem", O_CREAT, 0660, game->nb_philo);
	game->one_dead = sem_open("one_dead_sem", O_CREAT, 0660, 0);
	game->dead_print = sem_open("dead_print_sem", O_CREAT, 0660, 1);
	game->philo = malloc(game->nb_philo * sizeof(t_philo));
}
