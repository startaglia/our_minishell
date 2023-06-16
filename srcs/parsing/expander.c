/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:37:44 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/15 23:30:06 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_strdupfrom(char const *s, int inizio, int fine)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc (sizeof (char) * (fine - inizio + 1));
	while (inizio < fine)
	{
		newstr[i] = s[inizio];
		inizio++;
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}

char    *ft_findvalue(char *name, char **env)
{
    int     i;

    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(name, env[i], ft_strlen(name)))
            return (trim_def(env[i]));
        i++;
    }
    return (strdup(""));
}

char    *expander(char *line, t_shell *shell)
{
    char    *expanded;
    char    *varname;
    char    *varvalue;
    int i;
    int k;
    int start;

    varname = NULL;
    varvalue = NULL;
    expanded = malloc(sizeof(char) * 512);
    i = 0;
    k = 0;
    start = 0;
    while (line[i])
    {
        if (line[i] == 34)
            i++;
        if (line[i] == 39)
        {
            while (line[i] && line[i] != 39)
                i++;
        }
        if (line[i] == 36)
        {
            if (line[i + 1] == '?')
            {
                if (line[i + 2] == 34 || line[i + 2] == ' ' || !line[i + 2])
                {
                    varvalue = ft_itoa(exit_status);
                    expanded = strcat(expanded, varvalue);
                    free(varvalue);
                    i = i + 2;
                    if (line[i] == 34)
                        i++;
                    k = k + 1;
                    continue ;
                }
            }
            else
            {
                i++;
                start = i;
                while (line[i] && line[i + 1] != ' ')
                    i++;
                if (line[i - 1] == 34)
                    i--;
                varname = ft_strdupfrom(line, start, i);
                if (varname)
                    i++;
                varvalue = ft_findvalue(varname, shell->copy_env);
                free (varname);
                expanded = strcat(expanded, varvalue);
                if (line[i] && line[i] == 34)
                    i++;
                free(varvalue);
                k = ft_strlen(expanded);
            }
        }
        else
        {
            while (line[i] && line[i] != 36)
            {
                if (line[i] == 34 || line[i] == '~')
                    break ;
                expanded[k] = line[i];
                i++;
                k++;
            }
        }
        if (line[i] == '~')
        {
            if (line[i + 1] == 34 || !line[i + 1] || line[i + 1] != '~')
            {
                varvalue = ft_findvalue("HOME", shell->copy_env);
                expanded = strcat(expanded, varvalue);
                k = ft_strlen(expanded);
                free(varvalue);
                i++;
            }
        }
        expanded[k] = '\0';
    }
    k = 0;
    size_t check = 0;
    if (expanded[k])
    {
        while (expanded[check] == ' ')
            check++;
        if (check == ft_strlen(expanded))
        {
            free(expanded);
            expanded = ft_strdup("");
        }
    }
    return (expanded);
}
