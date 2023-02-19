/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:43:09 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/19 11:00:36 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	free_data(t_philosopher *philos);

int	main(int argc, char **argv)
{
	sem_t			*forks;
	t_philosopher	*philos;
	t_status		status;

	if (!is_valid_input(argc, argv))
	{
		printf("Invalid args: usage is <nbr_of_philo> <time_to_die> " \
					"<time_to_eat> <time_to_sleep> <must_eat>\n");
		return (EXIT_FAILURE);
	}
	init_status(argv, &status);
	forks = init_forks(&status);
	if (!forks)
		return (EXIT_FAILURE);
	philos = init_philosophers(&status, &forks);
	if (!philos)
	{
		sem_unlink("/forks");
		sem_close(philos->forks);
		return (EXIT_FAILURE);
	}
	set_dinner(&status, philos);
	free_data(philos);
	return (0);
}

static void	free_data(t_philosopher *philos)
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
	free(philos);
}
