/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:38:40 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/24 10:30:59 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	set_check(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	char	*fill_d(char *restrict dest, const char *restrict src, size_t l)
{
	size_t	i;

	i = 0;
	while (i < l)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*d;
	size_t	full_length;

	if (!set || !s1)
		return (NULL);
	while (s1)
	{
		if (set_check(((char)*s1), set) == 1)
			s1++;
		else
			break ;
	}
	full_length = ft_strlen(s1);
	while (full_length != 0)
	{
		if (set_check(s1[full_length - 1], set) == 1)
			full_length--;
		else
			break ;
	}
	d = (char *) malloc (full_length * sizeof(char) + 1);
	if (!d)
		return (NULL);
	d = fill_d(d, s1, full_length);
	return (d);
}
