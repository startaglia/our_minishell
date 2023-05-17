/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:17:48 by scastagn          #+#    #+#             */
/*   Updated: 2023/05/16 10:38:30 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim2(char *str, char del)
{
	int		i;
	int		j;
	int		count;
	char	*rtr;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == del)
			count++;
	}
	rtr = (char *)malloc(sizeof(char) * (ft_strlen(str) - count + 1));
	if (!rtr)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != del)
			rtr[j++] = str[i];
		i++;
	}
	rtr[j++] = '\0';
	return (rtr);
}
