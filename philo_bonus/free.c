/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:28:35 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/12 18:55:31 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_thread(t_pars *game, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i != game->nb_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

void	free_philo(t_pars *game)
{
	int	i;

	i = 0;
	while (i != game->nb_philo)
	{
		pthread_mutex_destroy(&game->philo[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(&game->printf);
	pthread_mutex_destroy(&game->alive_m);
	pthread_mutex_destroy(&game->last_meal_m);
	pthread_mutex_destroy(&game->dead_m);
	pthread_mutex_destroy(&game->time_m);
	free(game->philo);
}
