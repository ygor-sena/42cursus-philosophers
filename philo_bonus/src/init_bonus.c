/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:05:06 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/20 18:35:58 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_status(char **argv, t_status *status)
{
	sem_unlink("/lock_output");
	sem_unlink("/lock_repetitions");
	sem_unlink("/lock_dinner");
	sem_unlink("/lock_last_meal");
	sem_unlink("/lock_stop");
	status->total_philo = to_natural_nbr(argv[1]);
	status->time_of_death = to_natural_nbr(argv[2]);
	status->time_of_eating = to_natural_nbr(argv[3]);
	status->time_of_sleeping = to_natural_nbr(argv[4]);
	status->meals_to_eat = -1;
	if (argv[5])
		status->meals_to_eat = to_natural_nbr(argv[5]);
	status->start_time = get_current_time();
	status->stop_dinner = FALSE;
	status->sem_output = sem_open("/lock_output", O_CREAT, 0644, 1);
	status->sem_dinner = sem_open("/lock_dinner", O_CREAT, 0644, 1);
	status->sem_last_meal = sem_open("/lock_last_meal", O_CREAT, 0644, 1);
	status->sem_stop = sem_open("/lock_stop", O_CREAT, 0644, 0);
}

sem_t	*init_forks(t_status *status)
{
	sem_t	*forks;

	sem_unlink("/forks");
	forks = sem_open("/forks", O_CREAT, 0644, status->total_philo);
	if (!forks)
		return (NULL);
	return (forks);
}

t_philosopher	*init_philosophers(t_status *status, sem_t **forks)
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
		philos[i].left_fork = *forks;
		philos[i].right_fork = *forks;
		philos[i].status = status;
		philos[i].eat_again = 0;
		philos[i].last_meal = status->start_time;
		philos[i].forks = *forks;
		philos[i].philo_addr = (void *) philos;
		i++;
	}
	return (philos);
}
