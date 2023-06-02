/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:08:01 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/20 12:58:58 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	k;

	k = 0;
	while (s[k] != 0)
	{
		if (s[k] == (char)c)
			return ((char *)s + k);
		k++;
	}
	if (s[k] == (char)c)
		return ((char *)s + k);
	return (NULL);
}
