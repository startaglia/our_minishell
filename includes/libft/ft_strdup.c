/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:56:02 by dcarassi          #+#    #+#             */
/*   Updated: 2023/01/21 19:58:04 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	size_t	len_s1;
	char	*s2;

	len_s1 = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * (len_s1 + 1));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, (len_s1 + 1));
	return (s2);
}
