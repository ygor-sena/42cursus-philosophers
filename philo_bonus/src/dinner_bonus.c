/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:32:32 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/19 10:57:06 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_dinner(t_status *status, t_philosopher *philos)
{
	pthread_t		manager;
	size_t			i;

	i = -1;
	while (++i < status->total_philo)
		process_create(&philos[i].process, &start_dinner, &philos[i]);
	pthread_create(&manager, NULL, thread_manager, philos);
	i = -1;
	process_join(philos);
	pthread_join(manager, NULL);
}

int	start_dinner(void *philo_sits_down)
{
	t_philosopher	*philo;

	philo = philo_sits_down;
	if (philo->status->total_philo == 1)
	{
		print_status(philo, TAKING_FORK);
		usleep(philo->status->time_of_death * 1000);
		return (0);
	}
	while (!stop_dinner(philo->status))
	{
		eating(philo);
		if (philo->eat_again == philo->status->meals_to_eat)
		{
			sem_wait(philo->status->mutex_repetitions);
			philo->status->meals_repetitions += 1;
			sem_post(philo->status->mutex_repetitions);
			break ;
		}
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}

t_bool	stop_dinner(t_status *philo_status)
{
	sem_wait(philo_status->mutex_dinner);
	if (philo_status->stop_dinner == TRUE)
	{
		sem_post(philo_status->mutex_dinner);
		return (TRUE);
	}
	sem_post(philo_status->mutex_dinner);
	return (FALSE);
}

size_t	print_status(t_philosopher *philo, t_action action)
{
	size_t	current_time;
	size_t	time_spent;

	current_time = get_current_time();
	time_spent = current_time - philo->status->start_time;
	sem_wait(philo->status->mutex_output);
	if (action == TAKING_FORK)
		printf(FORK_LOG, time_spent, philo->philo_name);
	else if (action == EATING)
		printf(FORK_LOG FORK_LOG EAT_LOG, time_spent, \
					philo->philo_name, time_spent, philo->philo_name, \
					time_spent, philo->philo_name);
	else if (action == SLEEPING)
		printf(SLEEP_LOG, time_spent, philo->philo_name);
	else if (action == DEAD)
		printf(DEATH_LOG, time_spent, philo->philo_name);
	else if (action == THINKING)
		printf(THINK_LOG, time_spent, philo->philo_name);
	sem_post(philo->status->mutex_output);
	return (current_time);
}
