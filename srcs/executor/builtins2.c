/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:10:59 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/09 22:37:00 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    update_cwd(t_shell *shell)
{
    int     i;
    char    cwd[1024];
    char    *oldpwd;

    i = 0;
    getcwd(cwd, sizeof(cwd));
    while (shell->copy_env[i])
    {
        if (!ft_strncmp("PWD=", shell->copy_env[i], 4))
        {
            oldpwd = ft_strdup(shell->copy_env[i]);
            free(shell->copy_env[i]);
            shell->copy_env[i] = ft_strjoin("PWD=", cwd);
        }
        else if (!ft_strncmp("OLDPWD=", shell->copy_env[i], 7))
        {
            free(shell->copy_env[i]);
            shell->copy_env[i] = ft_strjoin("OLD", oldpwd);
            free(oldpwd);
        }
        i++;
    }
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

int ft_check_var(char **copy_env, t_command *cmd)
{
    int     i;
    
    i = 0;
    while (copy_env[i])
    {
        if (!strcmp(copy_env[i], cmd->split_cmd[1]))
            return (1);
        i++;
    }
    return (0);
}

void    ft_export(t_shell *shell, t_command *cmd)
{
    int     i;
    char    **updated_env;

    i = 0;
    if (!cmd->split_cmd[1])
        return (ft_env(shell->copy_env));
    if (ft_check_var(shell->copy_env, cmd))
        return ;
    while (shell->copy_env[i])
        i++;
    updated_env = (char **)malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (shell->copy_env[i])
    {
        updated_env[i] = ft_strdup(shell->copy_env[i]);
        i++;
    }
    updated_env[i] = ft_strdup(cmd->split_cmd[1]);
    updated_env[++i] = NULL;
    free_matrix(shell->copy_env);
    shell->copy_env = updated_env; 
}