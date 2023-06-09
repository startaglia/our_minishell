/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:40:11 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/08 22:43:17 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char     *ft_find_heredoc(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (!strcmp(cmd[i], "<<"))
        {
            if (cmd[i + 1])
                return (cmd[i + 1]);
            i++;
        }
        i++;
    }
    return (NULL);
}

char    *trim_def(char *full)
{
    int     i;
    int     count;
    char    *trimmed;

    i = 0;
    count = 0;
    while (full[i])
    {
        if (full[i] == 61)
        {
            i++;
            while (full[i])
            {
                i++;
                count++;
            }
        }
        i++;
    }
    trimmed = malloc(sizeof(char) * (count + 1));
    i = 0;
    count = 0;
    while (full[i])
    {
        if (full[i] == 61)
        {
            i++;
            while (full[i])
            {
                trimmed[count] = full[i];
                i++;
                count++;
            }
        }
        i++;
    }
    trimmed[count] = 0;
    return (trimmed);
}