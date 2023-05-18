/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:58:11 by dcarassi          #+#    #+#             */
/*   Updated: 2023/01/21 14:59:25 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_length(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n / 10 > 0 && i++)
		n = n / 10;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*d;
	long	nb;
	size_t	len;

	nb = n;
	len = get_length(nb) + 1;
	d = (char *)malloc(sizeof(char) * len);
	if (!d)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		d[0] = '-';
	}
	d[--len] = '\0';
	if (nb == 0)
		d[0] = '0';
	while (nb)
	{
		d[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (d);
}
