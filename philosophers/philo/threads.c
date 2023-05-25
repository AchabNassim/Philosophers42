/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:08:46 by nachab            #+#    #+#             */
/*   Updated: 2023/05/25 20:28:58 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->lock);
	if (*(philo->deaths) == 0)
	{
		printf("%llu %d %s", t_elapsed() - philo->start, philo->id, message);
	}
	pthread_mutex_unlock(philo->lock);
}

void	philo_ate(t_philo *philo)
{
	print_message(philo, "is eating\n");
	pthread_mutex_lock(philo->lock);
	philo->last_meal = t_elapsed();
	pthread_mutex_unlock(philo->lock);
	ft_sleep(philo->time_eat);
	pthread_mutex_lock(philo->lock);
	philo->meals += 1;
	if (philo->must_eat != 0 && philo->meals == philo->must_eat)
		*(philo->finished) += 1;
	pthread_mutex_unlock(philo->lock);
}

void	routine(t_philo *philo)
{
	print_message(philo, "is thinking\n");
	pthread_mutex_lock(&philo->forks[philo->left]);
	print_message(philo, "has taken a fork\n");
	if (philo->philo_nb == 1)
	{
		pthread_mutex_unlock(&philo->forks[philo->left]);
		ft_sleep(philo->time_die + 1);
		return ;
	}
	pthread_mutex_lock(&philo->forks[philo->right]);
	print_message(philo, "has taken a fork\n");
	philo_ate(philo);
	pthread_mutex_unlock(&philo->forks[philo->left]);
	pthread_mutex_unlock(&philo->forks[philo->right]);
	print_message(philo, "is sleeping\n");
	ft_sleep(philo->time_sleep);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		routine(philo);
		pthread_mutex_lock(philo->lock);
		if (*(philo->finished) == philo->philo_nb || *(philo->deaths) > 0)
		{
			pthread_mutex_unlock(philo->lock);
			break ;
		}
		pthread_mutex_unlock(philo->lock);
	}
	return (NULL);
}
