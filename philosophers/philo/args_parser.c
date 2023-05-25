/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:51:01 by nachab            #+#    #+#             */
/*   Updated: 2023/05/25 18:29:30 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	valid_number(char *arr)
{
	while (*arr == ' ' || *arr == '\t')
		arr++;
	if (*arr == '+' || *arr == '-')
		arr++;
	if (*arr == '\0')
		return (-1);
	while (*arr != '\0')
	{
		if (ft_isdigit(*arr) != 1 && *arr != ' ' && *arr != '\t')
			return (-1);
		arr++;
	}
	return (0);
}

int	valid_param(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (-1);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) < 0
		|| ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0
		|| (ac == 6 && ft_atoi(av[5]) <= 0))
		return (-1);
	return (0);
}

int	parse_args(int ac, char **av, t_philo **philos)
{
	if (valid_param(ac, av) == -1)
		return (-1);
	*philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!*philos)
		return (-1);
	if (init_philos(ac, av, *philos) == -1)
	{
		free_ressources(*philos, 1);
		return (-1);
	}
	if (init_mutexes(*philos) == -1)
	{
		free_ressources(*philos, 2);
		return (-1);
	}
	return (0);
}
