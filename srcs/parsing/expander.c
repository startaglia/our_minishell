/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:37:44 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/17 12:38:56 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *expand_quotes(char *line, int *i, int *k, char *expanded)
{
    (*i)++;
    while (line[*i] && line[*i] != 39)
    {
        expanded[*k] = line[*i];
        (*k)++;
        (*i)++;
    }
    if (line[*i] != '\0')
        (*i)++;
    expanded[*k] = '\0';
    return expanded;
}

char *expand_variable(char *line, int *i, int *k, char *expanded, t_shell *shell)
{
    int start;
    char    *varname;
    char    *varvalue;

    start = *i;
    while (ft_isalpha(line[*i]) && line[*i])
        (*i)++;
    varname = ft_strdupfrom(line, start, *i);
    varvalue = ft_findvalue(varname, shell->copy_env);
    free(varname);
    if (!varvalue)
        return expanded;
    expanded = strcat(expanded, varvalue);
    *k = ft_strlen(expanded);
    free(varvalue);
    return expanded;
}

char    *expand_the_rest(int *i, int *k, char *expanded, char *line)
{
    if (line[*i] != '\0')
    {
        expanded[*k] = line[*i];
        (*i)++;
        (*k)++;
        expanded[*k] = '\0';
    }
    return (expanded);
}

void    loop_expander(char *line, char *expanded, int *i, int *k, t_shell *shell)
{
    while (line[*i])
    {
        if (line[*i] == 39)
        {
            expanded = expand_quotes(line, i, k, expanded);
            continue;
        }
        if (line[*i] == 36)
        {
            (*i)++;
            if (line[*i] == 63)
            {
                expand_exit_status(i, k, expanded);
                continue;
            }
            expanded = expand_variable(line, i, k, expanded, shell);
            continue;
        }
        if (line[*i] == '~' && line[*i - 1] == ' ')
        {
            expanded = expand_home_directory(line, i, k, expanded, shell);
            continue;
        }
        expanded = expand_the_rest(i, k, expanded, line);
    }
}

char *expander(char *line, t_shell *shell)
{
    char *expanded;
    int i; 
    int k;

    i = 0;
    k = 0;
    if (!ft_check_if_expanded(line))
        return ft_strdup(line);
    expanded = malloc(sizeof(char) * 1024);
    expanded[0] = '\0';
    loop_expander(line, expanded, &i, &k, shell);
    expanded[k] = '\0';
    return expanded;
}