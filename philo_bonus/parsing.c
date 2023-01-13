/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:41:46 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/13 09:16:34 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_dead(t_philo *philo)
{
	int	between_meal;

	pthread_mutex_lock(&philo->game->last_meal_m);
	between_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->game->last_meal_m);
	if (between_meal > philo->game->time_to_die)
	{
		print_philo(philo, RED, DIED);
		pthread_mutex_lock(&philo->game->alive_m);
		philo->alive = false;
		pthread_mutex_unlock(&philo->game->alive_m);
	}
}

void	check_dead(t_pars *game)
{
	int		i;
	bool	dead;

	dead = false;
	while (1)
	{
		i = 0;
		while (i != game->nb_philo)
		{
			is_dead(&game->philo[i]);
			if (game->philo[i].alive == false)
			{
				pthread_mutex_lock(&game->dead_m);
				game->dead = true;
				dead = true;
				pthread_mutex_unlock(&game->dead_m);
				break ;
			}
			i++;
		}
		if (dead == true || game->meal == game->nb_philo)
			break ;
		usleep(1000);
	}
}

void	init_prog(t_pars *game, int argc, char **argv)
{
	int			i;
	pthread_t	*thread;

	i = 0;
	init_game(game, argc, argv);
	thread = malloc(game->nb_philo * sizeof(pthread_t));
	while (i != game->nb_philo)
	{
		if (i == 0)
			game->philo[i].l_fork = &game->philo[game->nb_philo - 1].r_fork;
		else
			game->philo[i].l_fork = &game->philo[i - 1].r_fork;
		init_philo(i, &game->philo[i], game);
		pthread_create(&thread[i], NULL, routine, &game->philo[i]);
		i++;
	}
	check_dead(game);
	join_thread(game, thread);
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
