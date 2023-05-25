/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 22:54:03 by nachab            #+#    #+#             */
/*   Updated: 2023/05/25 18:53:10 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->philo_nb)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

void	destroy_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philo->lock);
	while (i < philo->philo_nb)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
}

void	free_ressources(t_philo *philos, int code)
{
	if (code == 1)
		free(philos);
	else
	{
		destroy_mutexes(philos);
		if (philos->lock)
			free(philos->lock);
		if (philos->forks)
			free(philos->forks);
		if (philos->deaths)
			free(philos->deaths);
		if (philos->finished)
			free(philos->finished);
		if (philos)
			free(philos);
	}
}
