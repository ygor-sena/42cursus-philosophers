/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:45:14 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/19 10:17:44 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void		raise_stop_dinner(t_status *philo_status);
static t_bool	is_stuffed(t_status *philo_status);
static t_bool	died_of_starvation(t_philosopher *philo);

void	*thread_manager(void *arg)
{
	t_philosopher	*philo;
	t_status		*status;
	size_t			count;

	philo = (t_philosopher *)arg;
	status = philo[0].status;
	while (!is_stuffed(status))
	{
		count = 0;
		while (count < status->total_philo)
		{
			if (died_of_starvation(&philo[count]))
			{
				raise_stop_dinner(status);
				print_status(&philo[count], DEAD);
				return (NULL);
			}
			count++;
		}
		usleep(3000);
	}
	return (NULL);
}

static t_bool	is_stuffed(t_status *philo_status)
{
	t_bool	boolean;

	boolean = FALSE;
	sem_wait(philo_status->mutex_repetitions);
	if (philo_status->meals_repetitions == philo_status->total_philo)
		boolean = TRUE;
	sem_post(philo_status->mutex_repetitions);
	return (boolean);
}

static t_bool	died_of_starvation(t_philosopher *philo)
{
	long	last_meal;

	sem_wait(philo->status->mutex_last_meal);
	last_meal = get_current_time() - philo->last_meal;
	sem_post(philo->status->mutex_last_meal);
	if (last_meal > philo->status->time_of_death)
		return (TRUE);
	return (FALSE);
}

static void	raise_stop_dinner(t_status *philo_status)
{
	sem_wait(philo_status->mutex_dinner);
	philo_status->stop_dinner = TRUE;
	sem_post(philo_status->mutex_dinner);
}
