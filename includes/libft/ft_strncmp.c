/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:22:09 by dcarassi          #+#    #+#             */
/*   Updated: 2023/01/21 19:26:29 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	a;

	if (!s1 || !s2 || n == 0)
		return (0);
	a = 0;
	while ((s1[a] != '\0' || s2[a] != '\0') && a <= (n - 1))
	{
		if (s1[a] == s2[a])
			a++;
		else
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
	}
	return (0);
}
