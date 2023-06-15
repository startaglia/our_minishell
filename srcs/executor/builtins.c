/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:02:37 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/11 10:53:10 by scastagn         ###   ########.fr       */
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
    return (0);
}

void    ft_echo(char **args)
{
    int i;
    size_t j;
    int newline;

    i = 1;
    if (!strcmp(args[1], "-n"))
    {
        newline = 1;
        i++;
    }
    else
        newline = 0;
    while (args[i])
    {
        j = 0;
        while (j < ft_strlen(args[i]))
        {
            if (args[i][j] == 34)
                j++;
            write(1, &args[i][j], 1);
            j++;
        }
        write(1, " ", 1);
        i++;
    }
    if (!newline)
            printf("\n");
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

void    ft_cd(t_shell *shell, t_command *cmd)
{
    if (cmd->split_cmd[1])
    {
        if (!strcmp(cmd->split_cmd[1], "-"))
            update_cwd_reverse(shell);
        else if (chdir(cmd->split_cmd[1]) != 0)
            printf("minishell: cd: %s: No such file or directory\n", cmd->split_cmd[1]);
        else
            update_cwd(shell);
    }
    else
        ft_back_home(shell);
}