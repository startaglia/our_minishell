/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:02:37 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/08 22:43:28 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_is_builtin(char *cmd)
{
    if (!strcmp(cmd, "echo"))
        return (1);
    else if (!strcmp(cmd, "pwd"))
        return (2);
    else if (!strcmp(cmd, "env"))
        return (3);
    else if (!strcmp(cmd, "cd"))
        return (777);
    return (0);
}

void    update_cwd(t_shell *shell)
{
    int     i;
    char    cwd[1024];

    i = 0;
    getcwd(cwd, sizeof(cwd));
    while (shell->copy_env[i])
    {
        if (!ft_strncmp("PWD=", shell->copy_env[i], 4))
        {
            free(shell->copy_env[i]);
            shell->copy_env[i] = ft_strjoin("PWD=", cwd);
        }
        i++;
    }
}

void    ft_pwd(char **env)
{
    int i;
    int start;
    
    i = 0;
    start = 3;

    while (env[i])
    {
        if (!ft_strncmp("PWD=", env[i], 4))
            while(env[i][++start])
                write(1, &env[i][start], 1);
        i++;
    }
    printf("\n");
}

void    ft_env(char **env)
{
    int i;
    
    i = -1;
    while (env[++i])
        printf("%s\n", env[i]);
}

void    ft_cd(t_shell *shell, t_list *node)
{
    t_command *cmd;
    int i;
    char *dir;

    i = 0;
    cmd = ((t_command *)node->content);
    if (cmd->split_cmd[1])
    {
        if (chdir(cmd->split_cmd[1]) != 0)
        {
            printf("minishell: cd: %s: No such file or directory\n", cmd->split_cmd[1]);
            // shell->exit_status = 127;
            exit_status = 127;
        }
        else
        {
            update_cwd(shell);
            exit_status = 0;
        }
    }
    else
    {
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
}