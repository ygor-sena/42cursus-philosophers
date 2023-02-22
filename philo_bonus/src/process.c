/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:11:51 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/22 11:12:58 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	process_create(pid_t *process, int (*f)(void *), t_philosopher *philo)
{
	int	exit_status;

	exit_status = 0;
	*process = fork();
	if (*process == FORKED_CHILD)
	{
		pthread_create(&philo->manager, NULL, thread_manager, philo);
		exit_status = f(philo);
		pthread_join(philo->manager, NULL);
		exit_process(exit_status, philo);
	}
	return (exit_status);
}

int	process_join(t_philosopher *philos)
{
	size_t	i;
	int		exit_status;

	exit_status = 0;
	i = 0;
	while (i < philos->status->total_philo && exit_status == 0)
	{
		waitpid(-1, &exit_status, 0);
		exit_status = WEXITSTATUS(exit_status);
		i++;
	}
	if (exit_status)
	{
		i = 0;
		while (i < philos->status->total_philo)
		{
			kill(philos[i].process, SIGKILL);
			i++;
		}
	}
	return (exit_status);
}

void	exit_process(int exit_status, t_philosopher *philos)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT_STATUS);
	sem_unlink(SEM_STOP_DINNER);
	sem_unlink(SEM_LAST_MEAL);
	sem_unlink(SEM_IS_DEAD);
	sem_close(philos->sem_forks);
	sem_close(philos->status->sem_print_status);
	sem_close(philos->status->sem_stop_dinner);
	sem_close(philos->status->sem_last_meal);
	sem_close(philos->status->sem_is_dead);
	free(philos->philo_addr);
	exit(exit_status);
}
