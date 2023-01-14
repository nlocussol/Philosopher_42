/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:41:46 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/14 19:31:42 by nlocusso         ###   ########.fr       */
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
		kill(game->pid[i], SIGINT);
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
	sem_wait(game->printf_sem);
	while (i != game->nb_philo)
	{
		kill(game->pid[i], SIGINT);
		i++;
	}
	return (NULL);
}

void	check_eat_dead(t_pars *game)
{
	pthread_t	thread[2];

	if (game->total_meal != -1)
	{
		pthread_create(&thread[0], NULL, all_meal, game);
		pthread_detach(thread[0]);
	}
	pthread_create(&thread[1], NULL, dead, game);
	pthread_detach(thread[1]);
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
	free_philo(game);
}

int	pars_arg(int argc, char **argv)
{
	int	j;

	if (argv[1][0] == '0' || argv[argc - 1][0] == '0')
	{
		print_error(RED, "The number of philos cannot \
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
