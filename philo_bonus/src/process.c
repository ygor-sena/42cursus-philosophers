/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:11:51 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/19 15:19:54 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	process_create(pid_t *process, int (*f)(void *), t_philosopher *philo)
{
	int	exit_status;

	*process = fork();
	if (*process == FORKED_CHILD)
	{
		exit_status = f(philo);
		exit_program(exit_status, philo);
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

void	exit_program(int exit_status, t_philosopher *philos)
{
	sem_unlink("/lock_output");
	sem_unlink("/lock_repetitions");
	sem_unlink("/lock_dinner");
	sem_unlink("/lock_last_meal");
	sem_unlink("/forks");
	sem_close(philos->forks);
	sem_close(philos->status->mutex_output);
	sem_close(philos->status->mutex_repetitions);
	sem_close(philos->status->mutex_dinner);
	sem_close(philos->status->mutex_last_meal);
	free(philos->philo_addr);
	exit(exit_status);
}
