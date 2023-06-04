/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:12:11 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/20 13:01:39 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	k;

	k = ft_strlen(s);
	while (k >= 0)
	{
		if (s[k] == (char)c)
			return ((char *)s + k);
		k--;
	}
	return (NULL);
}
