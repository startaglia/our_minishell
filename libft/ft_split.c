/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:56:51 by dcarassi          #+#    #+#             */
/*   Updated: 2023/05/19 16:46:52 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strlen_neg_pos(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	count_words(const char *str, int c)
{
	int	count;
	int	flag;
	int	i;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (str[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static char	*copy_words(const char *str, int start, int end)
{
	char	*out;
	int		i;

	i = 0;
	out = (char *)malloc(sizeof(char) * ((end - start) + 1));
	while (start < end)
		out[i++] = str[start++];
	out[i] = 0;
	return (out);
}

char	**ft_split(char const *s, int c)
{
	char	**split;
	int		i;
	int		start;
	int		j;

	split = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!s || !split)
		return (0);
	start = -1;
	i = 0;
	j = 0;
	while (i <= strlen_neg_pos(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == strlen_neg_pos(s)) && start >= 0)
		{
			split[j++] = copy_words(s, start, i);
			start = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
