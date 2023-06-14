/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:36:23 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/20 11:40:49 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*newstr;

	i = 0;
	while (s1[i] != 0)
		i++;
	newstr = malloc(sizeof(char) * (i + 1));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}
