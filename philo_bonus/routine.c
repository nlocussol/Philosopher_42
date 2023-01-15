/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:59:16 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/15 11:30:22 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_routine(t_philo *philo)
{
	sem_wait(philo->game->fork);
	print_philo(philo, BLUE, FORK_R);
	sem_wait(philo->game->fork);
	print_philo(philo, BLUE, FORK_L);
	print_philo(philo, GREEN, EATING);
	ft_usleep(philo->game->time_to_eat, philo);
	sem_wait(philo->game->meal_sem);
	philo->last_meal = get_time();
	philo->nb_meal++;
	if (philo->nb_meal == philo->game->total_meal)
		sem_post(philo->game->all_eat);
	sem_post(philo->game->meal_sem);
	sem_post(philo->game->fork);
	sem_post(philo->game->fork);
}

void	sleep_routine(t_philo *philo)
{
	print_philo(philo, PINK, SLEEP);
	ft_usleep(philo->game->time_to_sleep, philo);
}

void	is_dead(t_philo *philo)
{
	int	between_meal;

	sem_wait(philo->game->meal_sem);
	between_meal = get_time() - philo->last_meal;
	sem_post(philo->game->meal_sem);
	if (between_meal >= philo->game->time_to_die)
	{
		sem_wait(philo->game->dead_print);
		print_philo(philo, RED, DIED);
		sem_wait(philo->game->printf_sem);
		philo->alive = false;
		sem_post(philo->game->one_dead);
	}
}

void	*manager(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	while (philo->alive != false)
	{
		usleep(10);
		is_dead(philo);
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, manager, philo);
	pthread_detach(thread);
	if (philo->id % 2 != 0)
		usleep(5000);
	while (1)
	{
		eat_routine(philo);
		sleep_routine(philo);
		print_philo(philo, YELLOW, THINK);
	}
	exit(EXIT_SUCCESS);
}
