/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:09:29 by nachab            #+#    #+#             */
/*   Updated: 2023/05/25 18:46:29 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# define ARGS_ERROR "\x1B[31m*+*+*\tPLEASE ENTER VALID ARGUMENTS!!\t*+*+*\n"
# define THREAD_ERROR "\x1B[31m*+*+*\tERROR TRYING TO INIT THE THREADS!\t*+*+*\n"

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	int				philo_nb;
	int				id;
	int				left;
	int				right;
	int				meals;
	int				*finished;
	int				*deaths;
	int				must_eat;
	uint64_t		start;
	uint64_t		last_meal;
	uint64_t		time_eat;
	uint64_t		time_die;
	uint64_t		time_sleep;
}	t_philo;

// PARSING FUNCTIONS //
int			ft_isdigit(char c);
int			valid_number(char *arr);
int			ft_atoi(char *nb);
int			parse_args(int ac, char **av, t_philo **philos);

// ALLOCATIONS AND INITIALISATION FUNCTIONS //
int			init_philos(int ac, char **av, t_philo *philos);
int			allocate_ressources(t_philo *philos);
void		init_values(int index, t_philo *philo);
void		init_time(char **av, t_philo *philo);
int			init_mutexes(t_philo *philos);
int			init_threads(t_philo *philos, int philo_nb);
int			init_prog(int ac, char **av, t_philo **philos);

// UTILS
uint64_t	t_elapsed(void);
void		*simulation(void *arg);
void		ft_sleep(uint64_t milli);

// EXIT FUNCTIONS //
void		join_threads(t_philo *philos);
void		free_ressources(t_philo *philo, int code);

#endif