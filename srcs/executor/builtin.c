#include "../../includes/minishell.h"

int ft_checkbuiltin(char *command)
{
    if (!ft_strncmp(command, "echo", 4) ||
        !ft_strncmp(command, "cd", 2) ||
        !ft_strncmp(command, "pwd", 3) ||
        !ft_strncmp(command, "env", 3) ||
        !ft_strncmp(command, "export", 6) ||
        !ft_strncmp(command, "unset", 5))
        return (1);
    return (0);
}

int ft_exec_builtin(char **cmd)
{
    if (!ft_strncmp(cmd[0], "cd", 2))
        ft_cd(cmd);
    else if (!ft_strncmp(cmd[0], "echo", 4))
        ft_echo(cmd);
    else if (!ft_strncmp(cmd[0], "pwd", 3))
        ft_pwd();
    // else if (!ft_strncmp(cmd[0], "env", 3))
    //     ft_env(cmd);
    // else if (!ft_strncmp(cmd[0], "export", 6))
    //     ft_export(cmd);
    // else if (!ft_strncmp(cmd[0], "unset", 5))
    //     ft_unset(cmd);
    return (0);
}