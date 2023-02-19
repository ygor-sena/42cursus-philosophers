/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:43:09 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/19 12:00:40 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_data(t_philosopher *philos, pthread_mutex_t **forks);

int	main(int argc, char **argv)
{
	pthread_mutex_t	**forks;
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
	philos = init_philosophers(&status, forks);
	if (!philos)
	{
		free_matrix((void **)forks, &status);
		return (EXIT_FAILURE);
	}
	set_dinner(&status, philos);
	free_data(philos, forks);
	return (0);
}

static void	free_data(t_philosopher *philos, pthread_mutex_t **forks)
{
	size_t	i;

	i = -1;
	while (++i < philos->status->total_philo)
		pthread_mutex_destroy(forks[i]);
	pthread_mutex_destroy(&philos->status->mutex_output);
	pthread_mutex_destroy(&philos->status->mutex_repetitions);
	pthread_mutex_destroy(&philos->status->mutex_dinner);
	pthread_mutex_destroy(&philos->status->mutex_last_meal);
	free_matrix((void **)forks, philos->status);
	free(philos);
}
