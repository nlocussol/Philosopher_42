/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:41:46 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/14 16:46:10 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	wait_pid(game);
	free_philo(game);
}

int	pars_arg(int argc, char **argv)
{
	int	j;

	while (argc != 1)
	{
		j = 0;
		while (argv[argc - 1][j])
		{
			if (argv[argc - 1][j] >= '0' && argv[argc - 1][j] <= '9')
				j++;
			else
				return (1);
		}
		argc--;
	}
	return (0);
}
