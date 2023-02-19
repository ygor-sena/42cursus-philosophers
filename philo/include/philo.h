/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:44:07 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/19 11:59:33 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK_LOG "%5ld %2ld has taken a fork\n"
# define EAT_LOG "%5ld %2ld is eating\n"
# define SLEEP_LOG "%5ld %2ld is sleeping\n"
# define THINK_LOG "%5ld %2ld is thinking\n"
# define DEATH_LOG "%5ld %2ld died\n"

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_action;

typedef struct s_status
{
	int				time_of_death;
	int				time_of_eating;
	int				time_of_sleeping;
	size_t			total_philo;
	size_t			meals_to_eat;
	size_t			meals_repetitions;
	size_t			start_time;
	t_bool			stop_dinner;
	pthread_mutex_t	mutex_output;
	pthread_mutex_t	mutex_repetitions;
	pthread_mutex_t	mutex_dinner;
	pthread_mutex_t	mutex_last_meal;
}	t_status;

typedef struct s_philosopher
{
	size_t			philo_name;
	size_t			eat_again;
	size_t			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_status		*status;
}	t_philosopher;

size_t			to_natural_nbr(char *arg);
t_bool			is_valid_input(int argc, char **argv);

void			init_status(char **argv, t_status *status);
pthread_mutex_t	**init_forks(t_status *status);
t_philosopher	*init_philosophers(t_status *status, \
						pthread_mutex_t **forks);

void			set_dinner(t_status *status, t_philosopher *philos);
void			*start_dinner(void *philo_sits_down);
t_bool			stop_dinner(t_status *philo_status);
size_t			print_status(t_philosopher *philo, t_action action);

void			eating(t_philosopher *philo);
void			thinking(t_philosopher *philo);
void			sleeping(t_philosopher *philo);

void			*thread_manager(void *arg);

int				ft_min(int a, int b);
int				ft_max(int a, int b);
long			get_current_time(void);
void			free_matrix(void **matrix, t_status *status);

#endif