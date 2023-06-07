/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:50:43 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/20 09:54:09 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			k;
	unsigned char	*new;

	k = 0;
	new = (unsigned char *)s;
	while (k < n)
	{
		new[k] = 0;
		k++;
	}
	s = new;
}
