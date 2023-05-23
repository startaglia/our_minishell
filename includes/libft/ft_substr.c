/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:35:04 by dcarassi          #+#    #+#             */
/*   Updated: 2023/01/20 12:20:54 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;
    size_t  j;

	if (!s)
      return (NULL);
	if ((int)start >= (int)ft_strlen(s))
      return (ft_strdup(""));
    if ((int)len > (int)ft_strlen(s))
      len = ft_strlen(s);
	d = (char *)malloc(sizeof(char) * (len + 1));
	if (!d)
      return (NULL);
	i = 0;
	j = 0;
    while (s[i])
	{
		if (i >= start && j < len)
          d[j++] = s[i];
        i++;
	}
	d[i] = 0;
	return (d);
}
