/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:19:51 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/19 10:59:39 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
