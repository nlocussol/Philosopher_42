/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:28:35 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/15 12:55:00 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_pid(t_pars *game)
{
	int	i;

	i = 0;
	while (i != game->nb_philo)
	{
		waitpid(game->pid[i], NULL, 0);
		i++;
	}
}

void	free_philo(t_pars *game)
{
	sem_close(game->printf_sem);
	sem_close(game->meal_sem);
	sem_close(game->alive_sem);
	sem_close(game->dead_sem);
	sem_close(game->time_sem);
	sem_close(game->fork);
	sem_close(game->all_eat);
	sem_close(game->one_dead);
	sem_close(game->dead_print);
	free(game->philo);
	free(game->pid);
}
