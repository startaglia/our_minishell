/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:59:32 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/17 15:17:04 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_changevalue(char **copy_env, t_command *cmd, int i)
{
    char    **myvar;
    char    **newvar;
    
    newvar = ft_split(cmd->split_cmd[1], 61);
    while (copy_env[i])
    {
        myvar = ft_split(copy_env[i], 61);
        if (!strcmp(newvar[0], myvar[0]) && newvar[1])
        {
            ft_changevalue_2(copy_env, cmd, i, newvar, myvar);
            return (1);
        }
        else if (!newvar[1] && !strcmp(newvar[0], myvar[0]))
        {
            ft_changevalue_3(copy_env, cmd, i, newvar, myvar);
            return (1);
        }
        else
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

    trimmed = trim_def_3(full, &i, &count);
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
            if (chdir(dir) != 0)
            {
                printf("minishell: cd: %s: No such file or directory\n", dir);
                g_exit_status = 1;
            }
            else
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