/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:07:08 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/19 11:10:47 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*newstr;
	unsigned int	i;
	size_t			len;

	i = 0;
	len = ft_strlen(s);
	newstr = malloc(sizeof(char) * len + 1);
	while (i < len)
	{
		newstr[i] = (*f)(i, s[i]);
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}
