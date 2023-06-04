/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:11:58 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/20 12:21:41 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *src, size_t n)
{
	size_t	k;

	k = 0;
	if (!dst && !src)
		return (NULL);
	else
	{
		while (k < n)
		{
			((unsigned char *)dst)[k] = ((unsigned char *)src)[k];
			k++;
		}
	}
	return (dst);
}
