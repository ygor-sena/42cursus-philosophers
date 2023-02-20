/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:15:26 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/20 18:34:30 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philosopher *philo)
{
	sem_wait(philo->left_fork);
	sem_wait(philo->right_fork);
	if (stop_dinner(philo->status))
	{
		sem_post(philo->right_fork);
		sem_post(philo->left_fork);
		return ;
	}
	philo->eat_again += 1;
	sem_wait(philo->status->sem_last_meal);
	philo->last_meal = print_status(philo, EATING);
	sem_post(philo->status->sem_last_meal);
	mssleep(philo->status->time_of_eating);
	sem_post(philo->right_fork);
	sem_post(philo->left_fork);
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
