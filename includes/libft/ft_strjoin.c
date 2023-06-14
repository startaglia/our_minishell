/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:44:31 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/24 09:47:11 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		k;
	int		j;
	size_t	joinsize;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	joinsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = malloc(sizeof (char) * joinsize);
	if (!join)
		return (NULL);
	k = 0;
	while (s1[k])
	{
		join[k] = s1[k];
		k++;
	}
	j = 0;
	while (s2[j])
		join[k++] = s2[j++];
	join [k] = 0;
	return (join);
}
