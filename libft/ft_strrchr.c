/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:16:58 by dcarassi          #+#    #+#             */
/*   Updated: 2023/01/21 19:20:17 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

    i = 0;
    if (!s)
      return (0);
    while (s[i])
      i++;
    while (i >= 0)
    {
      if (s[i] == (char)c)
        return ((char *)&s[i]);
      i--;
    }
	return (0);
}
