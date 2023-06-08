/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:42:48 by startagl          #+#    #+#             */
/*   Updated: 2023/06/08 11:47:06 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *skip_spaces(char *cmd)
{
	char *trimmed;
	int i;
	int k;

	k = 0;
	i = 0;
	while (cmd[i] == 32)
		i++;
	trimmed = malloc(sizeof(char) * (ft_strlen(cmd) - i + 1));
	while (cmd[i])
	{
		trimmed[k] = cmd[i];
		k++;
		i++;
	}
	trimmed[k] = 0;
	return (trimmed);
}

char **ft_add_pipes(char **pipe_words)
{
	int i;
	int k;
	char **new;
	char *trimmed;

	i = 0;
	k = 0;
	while (pipe_words[i])
		i++;
	new = (char **) malloc (sizeof(char *) * (i * 2));
	i = 0;
	while (pipe_words[i])
	{
		trimmed = skip_spaces(pipe_words[i]);
		new[k] = ft_strdup(trimmed);
		if (pipe_words[i + 1])
			new[++k] = ft_strdup("|");
		free(trimmed);
		i++;
		k++;
	}
	new[k] = NULL;
	return (new);
}

static int add_space(char *tmp, int i, char *line, int j)
{
	if (tmp[i] == 124)
	{	
		line[j] = 32;
		j++;
    	line[j] = tmp[i];
	}
    if (i != 0 && (tmp[i - 1] != 60 && tmp[i - 1] != 62))
    {
        line[j] = 32;
        j++;
    }
    line[j] = tmp[i];
    if (tmp[i + 1] != 60 && tmp[i + 1] != 62)
    {
        j++;
        line[j] = 32;
    }
    return j;
}

int		count_in_out(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if ((str[i] == 60 || str[i] == 62) && i != 0)
		{
			if (str[i - 1] != 60 && str[i - 1] != 62)
				k++;
			else if (str[i + 1] != 60 && str[i + 1] != 62)
				k++;
		}
		if (str[i] == 124)
			k++;
		i++;
	}
	return (k * 2);
}

char	*parsing(t_shell *shell)
{
	char	*str;
	int		i;
	int		j;
	int		space;

	i = 0;
	j = 0;
	// 	count_space ritorna il numero di simboli totali in / out, anche se trova un heredoc o un append conto inizialmente quanti sono in totale;
	space = count_in_out(shell->pipeline);
	str = (char *)malloc(sizeof(char *) + ft_strlen(shell->pipeline) + (space ) + 1);
	if (!str)
		return (NULL);
	while (shell->pipeline[i])
	{
		if (shell->pipeline[i] == 60 || shell->pipeline[i] == 62 || shell->pipeline[i] == 124)
			j = add_space(shell->pipeline, i, str, j);
		else
			str[j] = shell->pipeline[i];
		i++;
		j++;
	}
	str[j] = 0;
	return (str);
}
