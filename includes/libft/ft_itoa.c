/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:47:48 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/24 09:52:43 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		count++;
		n = -(n);
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_fillstr(char *nstr, int size, int n)
{
	int	k;

	k = size - 1;
	nstr[size] = 0;
	if (n < 0)
	{
		nstr[0] = '-';
		while (k > 0)
		{
			nstr[k] = (-(n % 10)) + 48;
			n = n / 10;
			k--;
		}
	}
	else
	{
		while (k >= 0)
		{
			nstr[k] = (n % 10) + 48;
			n = n / 10;
			k--;
		}
	}
	return (nstr);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*nstr;

	size = ft_count(n);
	nstr = malloc (sizeof(char) * size + 1);
	if (!nstr)
		return (NULL);
	nstr = ft_fillstr(nstr, size, n);
	return (nstr);
}
