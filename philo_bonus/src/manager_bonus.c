/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:45:14 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/22 11:19:18 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	died_of_starvation(t_philosopher *philo);
static void		raise_stop_dinner(t_philosopher *philo);

void	*thread_manager(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (philo->eat_again != philo->status->meals_to_eat)
	{
		if (died_of_starvation(philo))
		{
			raise_stop_dinner(philo);
			return (NULL);
		}
		usleep(3000);
	}
	return (NULL);
}

static t_bool	died_of_starvation(t_philosopher *philo)
{
	long	last_meal;

	sem_wait(philo->status->sem_last_meal);
	last_meal = get_current_time() - philo->last_meal;
	sem_post(philo->status->sem_last_meal);
	if (last_meal > philo->status->time_of_death)
		return (TRUE);
	return (FALSE);
}

static void	raise_stop_dinner(t_philosopher *philo)
{
	t_bool	no_queue;

	no_queue = TRUE;
	sem_wait(philo->status->sem_stop_dinner);
	if (*(int *)philo->status->sem_is_dead)
		no_queue = FALSE;
	sem_post(philo->status->sem_is_dead);
	sem_post(philo->status->sem_stop_dinner);
	if (no_queue)
		print_status(philo, DEAD);
}
