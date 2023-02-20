/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:44:07 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/20 18:40:45 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define FORK_LOG "%5ld %2ld has taken a fork\n"
# define EAT_LOG "%5ld %2ld is eating\n"
# define SLEEP_LOG "%5ld %2ld is sleeping\n"
# define THINK_LOG "%5ld %2ld is thinking\n"
# define DEATH_LOG "%5ld %2ld died\n"

# define FORKED_CHILD 0

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
	size_t			start_time;
	t_bool			stop_dinner;
	sem_t			*sem_output;
	sem_t			*sem_dinner;
	sem_t			*sem_last_meal;
	sem_t			*sem_stop;
}	t_status;

typedef struct s_philosopher
{
	void			*philo_addr;
	size_t			philo_name;
	size_t			eat_again;
	size_t			last_meal;
	sem_t			*left_fork;
	sem_t			*right_fork;
	sem_t			*forks;
	pid_t			process;
	t_status		*status;
	pthread_t		manager;
}	t_philosopher;

size_t			to_natural_nbr(char *arg);
t_bool			is_valid_input(int argc, char **argv);

void			init_status(char **argv, t_status *status);
sem_t			*init_forks(t_status *status);
t_philosopher	*init_philosophers(t_status *status, \
						sem_t **forks);

void			set_dinner(t_status *status, t_philosopher *philos);
int				start_dinner(void *philo_sits_down);
t_bool			stop_dinner(t_status *philo_status);
size_t			print_status(t_philosopher *philo, t_action action);

void			eating(t_philosopher *philo);
void			thinking(t_philosopher *philo);
void			sleeping(t_philosopher *philo);

void			*thread_manager(void *arg);

long			get_current_time(void);
void			mssleep(size_t ms_time);

int				process_create(pid_t *process, \
					int (*f)(void *), t_philosopher *philo);
int				process_join(t_philosopher *philos);
void			exit_program(int exit_status, t_philosopher *philos);

#endif