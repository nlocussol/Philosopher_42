/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:23:41 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/15 12:19:11 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_pars	game;

	if (argc < 5 || argc > 6)
	{
		print_error(RED, "You can put only 4 or 5 arguments!\n");
		return (1);
	}
	if (pars_arg(argc, argv) == 1)
		return (1);
	init_prog(&game, argc, argv);
	return (0);
}
