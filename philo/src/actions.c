/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:15:26 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/21 09:46:14 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosopher *philo)
{
	pthread_mutex_lock(philo->m_left_fork);
	pthread_mutex_lock(philo->m_right_fork);
	if (stop_dinner(philo->status))
	{
		pthread_mutex_unlock(philo->m_right_fork);
		pthread_mutex_unlock(philo->m_left_fork);
		return ;
	}
	philo->eat_again += 1;
	pthread_mutex_lock(&philo->status->m_last_meal);
	philo->last_meal = print_status(philo, EATING);
	pthread_mutex_unlock(&philo->status->m_last_meal);
	mssleep(philo->status->time_of_eating);
	pthread_mutex_unlock(philo->m_right_fork);
	pthread_mutex_unlock(philo->m_left_fork);
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
