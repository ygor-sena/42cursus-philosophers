/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:05:06 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/22 11:03:31 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_status(char **argv, t_status *status)
{
	sem_unlink(SEM_PRINT_STATUS);
	sem_unlink(SEM_STOP_DINNER);
	sem_unlink(SEM_LAST_MEAL);
	sem_unlink(SEM_IS_DEAD);
	status->total_philo = to_natural_nbr(argv[1]);
	status->time_of_death = to_natural_nbr(argv[2]);
	status->time_of_eating = to_natural_nbr(argv[3]);
	status->time_of_sleeping = to_natural_nbr(argv[4]);
	status->meals_to_eat = -1;
	if (argv[5])
		status->meals_to_eat = to_natural_nbr(argv[5]);
	status->start_time = get_current_time();
	status->stop_dinner = FALSE;
	status->sem_print_status = sem_open(SEM_PRINT_STATUS, O_CREAT, 0644, 1);
	status->sem_stop_dinner = sem_open(SEM_STOP_DINNER, O_CREAT, 0644, 1);
	status->sem_last_meal = sem_open(SEM_LAST_MEAL, O_CREAT, 0644, 1);
	status->sem_is_dead = sem_open(SEM_IS_DEAD, O_CREAT, 0644, 0);
}

sem_t	*init_forks(t_status *status)
{
	sem_t	*sem_forks;

	sem_unlink(SEM_FORKS);
	sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644, status->total_philo);
	if (!sem_forks)
		return (NULL);
	return (sem_forks);
}

t_philosopher	*init_philosophers(t_status *status, sem_t **sem_forks)
{
	t_philosopher	*philos;
	size_t			i;

	philos = malloc(status->total_philo * sizeof(t_philosopher));
	i = -1;
	if (!philos)
		return (NULL);
	i = 0;
	while (i < status->total_philo)
	{
		philos[i].philo_name = i + 1;
		philos[i].sem_left_fork = *sem_forks;
		philos[i].sem_right_fork = *sem_forks;
		philos[i].status = status;
		philos[i].eat_again = 0;
		philos[i].last_meal = status->start_time;
		philos[i].sem_forks = *sem_forks;
		philos[i].philo_addr = (void *) philos;
		i++;
	}
	return (philos);
}
