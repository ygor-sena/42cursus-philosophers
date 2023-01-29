/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:50:35 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/27 15:51:15 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdbool.h>

#define SIZE 3
#define LEFT (i + SIZE - 1) % SIZE
#define RIGHT (i + 1) % SIZE

#define THINKING 0
#define HUNGRY 1
#define EATING 2

// semaphore
//
// typedef struct s_ctrl {
// 	int				states[SIZE];
// 	pthread_mutex_t	mutex;
// }	t_ctrl;

int				state[SIZE];
pthread_t		philos[SIZE];
pthread_mutex_t	mutex;
int				sem[SIZE];

void	init_vec(int vec[]);
void	think(void);
void	test(int i);
void	take_forks(int i);
void	put_forks(int i);
void	*philosopher(void *n);

int	main(void)
{
	int	n;
	int idx;
	int	vector[SIZE];

	setbuf(stdout, NULL);
	// Inicializa semáforos
	// for (int i = 0; i < SIZE; i++)
	// {
	// 	sem[i] = sem_open("/philo", O_CREAT, 0660, 1);
	// }

	for (int i = 0; i < SIZE; i++)
	{
		sem[i] = 1;
	}
	// Inicializa mutex
	pthread_mutex_init(&mutex, NULL);

	// Inicializa threads
	for (long i = 0; i < SIZE; i++)
		pthread_create(&philos[i], 0, philosopher, (void *)i);
	for (long i = 0; i < SIZE; i++)
		pthread_join(philos[i], 0);
}

void	test(int i)
{
	if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
	{
		state[i] = EATING;
		printf("%ld take forks...\n", (long)i);
	}
	if (sem[i] == 0)
	{
		usleep(1000);
		sem[i] = 1;
	}
}

void	take_forks(int i)
{
	pthread_mutex_lock(&mutex);
	state[i] = HUNGRY;
	test(i);
	pthread_mutex_unlock(&mutex);
	if (sem[i] == 1)
	{
		usleep(3000);
		sem[i] = 0;
	}
	// sem_wait(&sem[i]);
}

void	put_forks(int i)
{
	pthread_mutex_lock(&mutex);
	state[i] = THINKING;
	printf("%ld put forks...\n", (long)i);
	test(LEFT);
	test(RIGHT);
	pthread_mutex_unlock(&mutex);
}

void	*philosopher(void *n)
{
	long i = (long)n;

	while (true)
	{
		think();
		take_forks(i);
		printf("%ld is eating...\n", (long)n);
		// eat();
		usleep(50000);
		put_forks(i);
	}
	return (NULL);
}

void	think(void)
{
	usleep(1000);
}

void	init_vec(int vec[])
{
	int	n;

	n = 0;
	while (n < SIZE)
	{
		vec[n] = n;
		n++;
	}
}
