/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:58:23 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/24 10:26:51 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	long_max(int j, int x)
{
	int	y;

	y = 0;
	if (j >= 19 && x == 1)
		y = -1;
	if (j >= 19 && x == -1)
		y = 0;
	return (y);
}

static int	check_sign(char c)
{
	int	sign;

	sign = 1;
	if (c == '-')
			sign *= -1;
	return (sign);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	res;
	int	counter;

	sign = 1;
	res = 0;
	counter = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = check_sign(*str);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - 48;
		counter++;
		str++;
	}
	if (counter >= 19)
		return (long_max(counter, sign));
	return (sign * res);
}
