/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:15:26 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/22 10:57:11 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philosopher *philo)
{
	sem_wait(philo->sem_left_fork);
	sem_wait(philo->sem_right_fork);
	if (stop_dinner(philo->status))
	{
		sem_post(philo->sem_right_fork);
		sem_post(philo->sem_left_fork);
		return ;
	}
	philo->eat_again++;
	sem_wait(philo->status->sem_last_meal);
	philo->last_meal = print_status(philo, EATING);
	sem_post(philo->status->sem_last_meal);
	mssleep(philo->status->time_of_eating);
	sem_post(philo->sem_right_fork);
	sem_post(philo->sem_left_fork);
}

void	thinking(t_philosopher *philo)
{
	if (stop_dinner(philo->status))
		return ;
	print_status(philo, THINKING);
}

void	sleeping(t_philosopher *philo)
{
	if (stop_dinner(philo->status))
		return ;
	print_status(philo, SLEEPING);
	mssleep(philo->status->time_of_sleeping);
}
