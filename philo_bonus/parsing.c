/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:41:46 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/16 09:59:50 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*dead(void *game_void)
{
	int		i;
	t_pars	*game;

	game = (t_pars *)game_void;
	sem_wait(game->one_dead);
	i = 0;
	while (i != game->nb_philo)
	{
		kill(game->pid[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i != game->nb_philo)
	{
		sem_post(game->all_eat);
		i++;
	}
	return (NULL);
}

void	*all_meal(void *game_void)
{
	int		i;
	t_pars	*game;

	i = 0;
	game = (t_pars *)game_void;
	while (i != game->nb_philo)
	{
		sem_wait(game->all_eat);
		i++;
	}
	i = 0;
	while (i != game->nb_philo)
	{
		kill(game->pid[i], SIGKILL);
		i++;
	}
	sem_post(game->one_dead);
	return (NULL);
}

void	check_eat_dead(t_pars *game)
{
	pthread_t	thread_dead;
	pthread_t	thread_eat;

	if (game->total_meal != -1)
	{
		pthread_create(&thread_eat, NULL, all_meal, game);
		pthread_detach(thread_eat);
	}
	pthread_create(&thread_dead, NULL, dead, game);
	pthread_detach(thread_dead);
}

void	init_prog(t_pars *game, int argc, char **argv)
{
	int			i;

	i = 0;
	init_game(game, argc, argv);
	while (i != game->nb_philo)
	{
		init_philo(i, &game->philo[i], game);
		game->pid[i] = fork();
		if (game->pid[i] == 0)
			routine(&game->philo[i]);
		i++;
	}
	check_eat_dead(game);
	wait_pid(game);
	usleep(10000);
	free_philo(game);
}

int	pars_arg(int argc, char **argv)
{
	int	j;

	if (argv[1][0] == '0' || argv[argc - 1][0] == '0')
	{
		print_error(RED, "The arguments cannot \
be equal to or less than 0!\n");
		return (1);
	}
	while (argc != 1)
	{
		j = 0;
		while (argv[argc - 1][j])
		{
			if (argv[argc - 1][0] == '+' || (argv[argc - 1][j] >= '0'
				&& argv[argc - 1][j] <= '9'))
				j++;
			else
			{
				print_error(RED, "Parameters can only \
be non-negative numbers!\n");
				return (1);
			}
		}
		argc--;
	}
	return (0);
}
