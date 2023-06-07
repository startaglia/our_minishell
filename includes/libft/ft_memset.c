/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:46:45 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/20 09:49:05 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			k;
	unsigned char	*new;

	k = 0;
	new = (unsigned char *)s;
	while (k < n)
	{
		new[k] = c;
		k++;
	}
	s = new;
	return (s);
}
