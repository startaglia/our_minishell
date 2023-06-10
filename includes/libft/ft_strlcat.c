/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:57:40 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/20 10:02:52 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	j = len_dst;
	if (dstsize == 0 || dstsize <= len_dst)
		return (len_src + dstsize);
	while (src[i] != 0 && i < dstsize - len_dst - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = 0;
	return (len_dst + len_src);
}
