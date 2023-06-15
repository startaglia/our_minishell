/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:37:44 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/16 00:51:48 by scastagn         ###   ########.fr       */
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
    return (NULL);
}

char    *expander(char *line, t_shell *shell)
{
    char    *expanded;
    char    *varname;
    char    *varvalue;
    int i;
    int k;
    int start;

    expanded = malloc(sizeof(char) * 1024);
    i = 0;
    k = 0;
    start = 0;
    while (line[i])
    {
        varvalue = NULL;
        if (line[i] == 36)
        {
            i++;
            if (line[i] == 63)
            {
                printf("vez fai qualcosa qui\n");
                //itoa exit_status ecc...
            }
            start = i;
            while (ft_isalpha(line[i]) && line[i])
                i++;
            varname = ft_strdupfrom(line, start, i);
            varvalue = ft_findvalue(varname, shell->copy_env);
            free (varname);
            if (!varvalue)
                continue ;
            expanded = strcat(expanded, varvalue);
            //k = start + ft_strlen(varvalue) -1 ;
            k = ft_strlen(expanded);
        }
        else
        {
            expanded[k] = line[i];
            i++;
            k++;
        }
        if (varvalue)
            free(varvalue);
        expanded[k] = 0;
    }
    return (expanded);
}
