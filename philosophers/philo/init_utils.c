/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 22:44:25 by nachab            #+#    #+#             */
/*   Updated: 2023/05/25 18:52:04 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_philo *philos)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(philos->lock, NULL) != 0)
		return (-1);
	while (i < philos->philo_nb)
	{
		if (pthread_mutex_init(&philos->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	init_time(char **av, t_philo *philo)
{
	static uint64_t	start;

	if (start == 0)
		start = t_elapsed();
	philo->start = start;
	philo->last_meal = start;
	philo->time_eat = ft_atoi(av[3]);
	philo->time_die = ft_atoi(av[2]);
	philo->time_sleep = ft_atoi(av[4]);
}

void	init_values(int index, t_philo *philo)
{
	philo->id = index + 1;
	philo->left = index;
	philo->right = (index + 1) % philo->philo_nb;
	philo->meals = 0;
	philo->must_eat = 0;
}

int	allocate_ressources(t_philo *philos)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	int				*deaths;
	int				*finished;

	forks = malloc(sizeof(pthread_mutex_t) * philos->philo_nb);
	lock = malloc(sizeof(pthread_mutex_t));
	deaths = malloc(sizeof(int));
	finished = malloc(sizeof(int));
	if (!forks || !deaths || !lock || !finished)
		return (-1);
	*deaths = 0;
	*finished = 0;
	philos->finished = finished;
	philos->forks = forks;
	philos->deaths = deaths;
	philos->lock = lock;
	return (0);
}

int	init_philos(int ac, char **av, t_philo *philos)
{
	int				i;
	int				philo_nb;

	i = 0;
	philo_nb = ft_atoi(av[1]);
	philos->philo_nb = philo_nb;
	if (allocate_ressources(philos) != 0)
		return (-1);
	while (i < philo_nb)
	{
		philos[i].forks = philos[0].forks;
		philos[i].lock = philos[0].lock;
		philos[i].deaths = philos[0].deaths;
		philos[i].finished = philos[0].finished;
		philos[i].philo_nb = philo_nb;
		init_time(av, philos + i);
		init_values(i, philos + i);
		if (ac == 6)
			philos[i].must_eat = ft_atoi(av[5]);
		i++;
	}
	return (0);
}
