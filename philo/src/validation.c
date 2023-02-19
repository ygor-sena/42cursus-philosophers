/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:11:53 by yde-goes          #+#    #+#             */
/*   Updated: 2023/02/18 13:44:42 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		ft_isdigit(int c);
static t_bool	is_natural_nbr(char *string);

t_bool	is_valid_input(int argc, char **argv)
{
	size_t	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (FALSE);
	while (i < (size_t) argc)
	{
		if (!is_natural_nbr(argv[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

size_t	to_natural_nbr(char *str)
{
	size_t	nbr_conv;

	nbr_conv = 0;
	while (*str)
	{
		nbr_conv = (nbr_conv * 10) + (*str - '0');
		str++;
	}
	return (nbr_conv);
}

static t_bool	is_natural_nbr(char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (!ft_isdigit(string[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	return (0);
}
