/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:51:38 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/20 14:01:04 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	k;
	size_t	j;

	k = 0;
	j = 0;
	if (!haystack && !needle)
		return (0);
	if (needle[0] == 0 || needle == haystack)
		return ((char *)haystack);
	while (k + j < len && haystack[k + j] != 0)
	{
		j = 0;
		while (haystack[k + j] == needle[j] && k + j < len)
			j++;
		if (!needle[j])
			return ((char *)(haystack + k));
		k++;
	}
	return (NULL);
}
