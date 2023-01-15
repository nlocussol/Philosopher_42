/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:52:35 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/15 12:59:29 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time, t_philo *philo)
{
	int	init_time;
	int	exit_time;

	init_time = get_time();
	exit_time = time + init_time;
	while (init_time <= exit_time)
	{
		pthread_mutex_lock(&philo->game->dead_m);
		if (philo->game->dead != false || philo->game->all_eat == true)
		{
			pthread_mutex_unlock(&philo->game->dead_m);
			break ;
		}
		pthread_mutex_unlock(&philo->game->dead_m);
		usleep(500);
		init_time = get_time();
	}
}

void	print_error(char *color, char *message)
{
	printf("%s", color);
	printf("%s", message);
	printf("\033[0m");
}

void	print_philo(t_philo *philo, char *color, char *message)
{
	int	time_now;

	pthread_mutex_lock(&philo->game->dead_m);
	pthread_mutex_lock(&philo->game->meal_m);
	pthread_mutex_lock(&philo->game->printf);
	if (philo->game->dead == false && philo->alive == true
		&& philo->game->all_eat == false)
	{
		time_now = get_time() - philo->game->time;
		printf("%s", color);
		printf("%d %d %s", time_now, philo->id, message);
		printf("\033[0m");
	}
	pthread_mutex_unlock(&philo->game->meal_m);
	pthread_mutex_unlock(&philo->game->printf);
	pthread_mutex_unlock(&philo->game->dead_m);
}

int	overflow(int number)
{
	if (number >= 0)
		return (-1);
	else
		return (0);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	long long	to_return;
	int			is_neg;

	i = 0;
	to_return = 0;
	is_neg = 1;
	while ((nptr[i] >= '\a' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
	{
		i++;
		is_neg = -1;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		to_return = to_return * 10 + (nptr[i] - 48);
		if (to_return * is_neg > LONG_MAX || to_return * is_neg < LONG_MIN)
			return (overflow(to_return * is_neg));
		i++;
	}
	return (to_return * is_neg);
}
