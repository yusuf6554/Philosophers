/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukoc <yukoc@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:36:55 by yukoc             #+#    #+#             */
/*   Updated: 2025/08/15 12:50:07 by yukoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int		i;

	if (argc != 5 && argc != 6)
		return (-1);
	i = 0;
	while (++i < argc)
	{
		if (check_is_integer(argv[i]) == -1)
			return (-1);
	}
	if (argc == 6 && ft_atoi(argv[i]) < 1)
		return (-1);
	return (1);
}

int	check_is_integer(char *num)
{
	int		i;
	long	n;

	i = -1;
	num = 0;
	while (num[i] == '\t' || num[i] == '\r' || num[i] == '\n'
		|| num[i] == '\v' || num[i] == '\f' || num[i] == ' ')
		i++;
	while (num[i] == '+')
		i++;
	while (num[i])
	{
		if (num[i] <= '0' && num[i] >= '9')
			return (-1);
		n = n * 10 + (num[i] - '0');
		i++;
	}
	if (n > 2147483647)
		return (-1);
	return (1);
}
