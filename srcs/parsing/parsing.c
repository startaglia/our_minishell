/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:42:48 by startagl          #+#    #+#             */
/*   Updated: 2023/05/13 12:33:08 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int	add_space(char *tmp, int i, char *line, int j)
{
	if (tmp[i - 1] != 60 && tmp[i - 1] != 62)
		line[j++] = 32;
	line[j] = tmp[i];
	if (tmp[i + 1] != 60 && tmp[i + 1] != 62)
		line[++j] = 32;
	return (j);
}

// 60(<) 62(>)
int		count_in_out(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == 60 || str[i] == 62)
		{
			if (str[i - 1] != 60 && str[i - 1] != 62)
				k++;
			else if (str[i + 1] != 60 && str[i + 1] != 62)
				k++;
		}
		i++;
	}
	return (k);
}

char	*parsing(t_shell *shell)
{
	char	*str;
	int		i;
	int		j;
	int		space;

	i = 0;
	j = 0;
	// 	count_space ritorna il numero di simboli totlai in / out, anche se trova un heredoc o un append conto inizialmente quanti sono in totale;
	space = count_in_out(shell->pipeline);
	printf("space %d\n", space);
	str = (char *)malloc(sizeof(char *) + ft_strlen(shell->pipeline) + (space * 2) + 1);
	if (!str)
		return (NULL);
	while (shell->pipeline[i])
	{
		if (shell->pipeline[i] == 60 || shell->pipeline[i] == 62)
			j = add_space(shell->pipeline, i, str, j);
		else
			str[j] = shell->pipeline[i];
		i++;
		j++;
	}
	str[j] = 0;
	return (str);
}
