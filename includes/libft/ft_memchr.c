/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:45:48 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/20 12:52:16 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	k;

	k = 0;
	if (!s)
		return (NULL);
	while (k < n)
	{
		if (((unsigned char *)s)[k] == (unsigned char)c)
			return ((void *)s + k);
		k++;
	}
	return (NULL);
}
