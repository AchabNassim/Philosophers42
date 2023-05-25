/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:51:07 by nachab            #+#    #+#             */
/*   Updated: 2023/05/03 15:23:00 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_philo *philo, int philo_nb)
{
	int	i;

	i = 0;
	while (i < philo_nb)
	{
		if (pthread_create(&philo[i].philo, NULL, simulation, &philo[i]) != 0)
			return (-1);
		i++;
		usleep(40);
	}
	return (0);
}

int	init_prog(int ac, char **av, t_philo **philos)
{
	if (parse_args(ac, av, philos) == -1)
	{
		printf("%s", ARGS_ERROR);
		return (1);
	}
	init_threads(*philos, (*philos)->philo_nb);
	return (0);
}
