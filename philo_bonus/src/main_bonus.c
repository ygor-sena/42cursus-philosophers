/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:43:09 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/23 10:34:02 by yde-goes         ###   ########.fr       */
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
		printf("Invalid args: usage is <nbr_of_philo>(>= 1) "\
				"<time_to_die>(>= 1) <time_to_eat>(>= 1) "\
				"<time_to_sleep>(>= 1) <must_eat>(optional).\n");
		return (EXIT_FAILURE);
	}
	init_status(argv, &status);
	forks = init_forks(&status);
	if (!forks)
		return (EXIT_FAILURE);
	philos = init_philosophers(&status, &forks);
	if (!philos)
	{
		sem_unlink(SEM_FORKS);
		sem_close(philos->sem_forks);
		return (EXIT_FAILURE);
	}
	set_dinner(&status, philos);
	free_data(philos);
	return (EXIT_SUCCESS);
}

static void	free_data(t_philosopher *philos)
{
	sem_close(philos->sem_forks);
	sem_close(philos->status->sem_print_status);
	sem_close(philos->status->sem_stop_dinner);
	sem_close(philos->status->sem_last_meal);
	sem_close(philos->status->sem_is_dead);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT_STATUS);
	sem_unlink(SEM_STOP_DINNER);
	sem_unlink(SEM_LAST_MEAL);
	sem_unlink(SEM_IS_DEAD);
	free(philos);
}
