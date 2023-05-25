/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:30:58 by nachab            #+#    #+#             */
/*   Updated: 2023/05/24 23:29:14 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *nb)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (valid_number(nb) != 0)
		return (-1);
	while (nb[i] == ' ')
		i++;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i] == '-')
			return (-1);
		i++;
	}
	while (nb[i] && ft_isdigit(nb[i]) == 1)
	{
		result = result * 10;
		result = result + (nb[i] - 48);
		i++;
	}
	if (result > INT_MAX)
		return (-1);
	return (result);
}

uint64_t	t_elapsed(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000LL));
}

void	ft_sleep(uint64_t milli)
{
	uint64_t	now;
	uint64_t	elapsed;

	now = t_elapsed();
	elapsed = t_elapsed();
	while (elapsed - now < milli)
	{
		usleep(1000);
		elapsed = t_elapsed();
	}
}
