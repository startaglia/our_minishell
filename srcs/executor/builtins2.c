/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:10:59 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/14 22:12:24 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    update_cwd(t_shell *shell)
{
    int     i;
    char    cwd[1024];
    char    *oldpwd;

    i = 0;
    oldpwd = NULL;
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
    exit_status = 0;
}

void    update_cwd_reverse(t_shell *shell)
{
    int     i;
    char    *trimmed;

    i = 0;
    while (shell->copy_env[i])
    {
        if (!ft_strncmp("OLDPWD=", shell->copy_env[i], 7))
        {
            trimmed = trim_def(shell->copy_env[i]);
            if (chdir(trimmed) != 0)
            {
                printf("minishell: cd: %s: No such file or directory\n", trimmed);
                exit_status = 1;
            }
            else
            {
                update_cwd(shell);
                printf("%s\n", trimmed);
            }
            free(trimmed);
        }
        i++;
    }
}

void    ft_export(t_shell *shell, t_command *cmd)
{
    int     i;
    char    **updated_env;

    i = 0;
    if (!cmd->split_cmd[1])
        return (ft_env(shell->copy_env));
    if (ft_check_var(shell->copy_env, cmd, 1))
        return ;
    if (ft_check_var(shell->copy_env, cmd, 2))
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
    exit_status = 0;
}

void    ft_unset(t_shell *shell, t_command *cmd)
{
    int     i;
    int     toskip;
    char    **updated_env;

    toskip = ft_findvar(shell, cmd);
    if (toskip != -1)
    {
        updated_env = (char **)malloc(sizeof(char *) * (get_matrix_lenght(shell->copy_env)));
        i = 0;
        while (shell->copy_env[i] && i < toskip)
        {
            updated_env[i] = ft_strdup(shell->copy_env[i]);
            i++;
        }
        while (shell->copy_env[++i])
        {
            updated_env[toskip] = ft_strdup(shell->copy_env[i]);
            toskip++;
        }
        updated_env[toskip] = NULL;
        free_matrix(shell->copy_env);
        shell->copy_env = updated_env;
    }
    exit_status = 0;
}
