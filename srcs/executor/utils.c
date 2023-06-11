/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:59:32 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/11 15:39:17 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_changevalue(char **copy_env, t_command *cmd, int i)
{
    char    *temp;
    char    **myvar;
    char    **newvar;
    
    newvar = ft_split(cmd->split_cmd[1], 61);
    while (copy_env[i])
    {
        myvar = ft_split(copy_env[i], 61);
        if (!strcmp(newvar[0], myvar[0]))
        {
            free(myvar[1]);
            myvar[1] = ft_strdup(newvar[1]);
            free(copy_env[i]);
            temp = ft_strjoin(myvar[0], "=");
            copy_env[i] = ft_strjoin(temp, myvar[1]);
            free(temp);
            free_matrix(myvar);
            free_matrix(newvar);
            return (1);
        }
        free_matrix(myvar);
        i++;
    }
    free_matrix(newvar);
    return (0);
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
            break ;
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
            break ;
        }
        i++;
    }
    trimmed[count] = 0;
    return (trimmed);
}

void    ft_back_home(t_shell *shell)
{
    int     i;
    char    *dir;

    i = 0;
    while (shell->copy_env[i])
    {
        if (!ft_strncmp("HOME=", shell->copy_env[i], 5))
        {
            dir = trim_def(shell->copy_env[i]);
            chdir(dir);
            update_cwd(shell);
            free(dir);
            }
            i++;
    }
}

int ft_check_var(char **copy_env, t_command *cmd, int mode)
{
    int     i;

    i = 0;
    if (mode == 1)
    {
        while (copy_env[i])
        {
            if (!strcmp(copy_env[i], cmd->split_cmd[1]))
                return (1);
            i++;
        }
    }
    else if (mode == 2)
        return (ft_changevalue(copy_env, cmd, i));
    return (0);
}

char    *getpath(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(env[i], "PATH=", 5))
            return (trim_def(env[i]));
        i++;
    }
    return (NULL);
}