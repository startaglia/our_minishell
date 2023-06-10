/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:40:25 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/24 09:43:53 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	k;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		start = ft_strlen(s);
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	substr = malloc (sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	k = 0;
	while (s[start] && len--)
	{
		substr[k] = s[start];
		k++;
		start++;
	}
	substr[k] = 0;
	return (substr);
}
