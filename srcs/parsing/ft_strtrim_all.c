/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:24:58 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/17 13:27:00 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**ft_strtrim_all(char **matrix)
{
	char	**newtrimmed;
	char	*tmp1;
	int		i;

	i = get_matrix_lenght(matrix);
	newtrimmed = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (matrix[i])
	{
		tmp1 = ft_strtrim2(matrix[i], 34);
		newtrimmed[i] = ft_strtrim2(tmp1, 39);
		free(tmp1);
		i++;
	}
	newtrimmed[i] = NULL;
	free_matrix(matrix);
	return (newtrimmed);
}
