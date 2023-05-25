/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:13:15 by nachab            #+#    #+#             */
/*   Updated: 2023/05/25 19:05:02 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death(t_philo *philo)
{
	uint64_t	elapsed;

	elapsed = t_elapsed();	
	if (elapsed - philo->last_meal > philo->time_die)
	{
		printf("%llu %d died\n", t_elapsed() - philo->start, philo->id);
		*(philo->deaths) += 1;
		return (1);
	}
	return (0);
}

int	finished_eating(t_philo *philo)
{
	if (philo->must_eat != 0 && *(philo->finished) == philo->philo_nb)
		return (1);
	return (0);
}

void	checker(t_philo *philos)
{
	int				i;
	int				deaths;
	int				finished;

	deaths = 0;
	finished = 0;
	while (1)
	{
		i = -1;
		while (++i < philos->philo_nb)
		{
			pthread_mutex_lock(philos[i].lock);
			deaths = death(&philos[i]);
			finished = finished_eating(&philos[i]);
			pthread_mutex_unlock(philos[i].lock);
			if (finished != 0 || deaths != 0)
				return ;
		}
	}
}

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (init_prog(ac, av, &philos) != 0)
	{
		return (1);
	}
	checker(philos);
	join_threads(philos);
	free_ressources(philos, 3);
	return (0);
}
