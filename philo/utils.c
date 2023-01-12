/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:52:35 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/12 18:13:41 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time, t_philo *philo)
{
	while (time >= 0)
	{
		if (philo->alive == false)
			break ;
		usleep(100);
		time -= 100;
	}
}

void	print_philo(t_philo *philo, char *color, char *message, int time)
{
	int	time_now;

	if (philo->game->dead == false)
	{
		time_now = get_time() - time;
		pthread_mutex_lock(&philo->game->printf);
		printf("%s", color);
		printf("%d %d %s", time_now, philo->id, message);
		printf("\033[0m");
		pthread_mutex_unlock(&philo->game->printf);
	}
}

int	get_time(void)
{
	struct timeval	tv_s;
	struct timezone	tv_u;
	int				time;

	gettimeofday(&tv_s, &tv_u);
	time = tv_s.tv_usec / 1000 + ((tv_s.tv_sec % 1000) * 1000);
	return (time);
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
