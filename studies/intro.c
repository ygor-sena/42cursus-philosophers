/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:54:48 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/26 19:50:25 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define TH_SIZE 8
int	mails = 0;
pthread_mutex_t	mutex;

void	*routine(void	*arg)
{
	(void) arg;
	/* printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n"); */
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}	
	//here, we're reading, incrementing and writing mails
}

int	main(void)
{
	pthread_t	th[TH_SIZE];
	size_t			i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < TH_SIZE; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL))
		{
			perror("Failed to create thread\n");
			return (EXIT_FAILURE);
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < TH_SIZE; i++)
	{
		if (pthread_join(th[i], NULL))
		{
			perror("Failed to join thread\n");
			return (EXIT_FAILURE);	
		}
		printf("Thread %d has finished\n", i);			
	}
	printf("Number of mails: %d", mails);
	pthread_mutex_destroy(&mutex);
	return (EXIT_SUCCESS);
}
