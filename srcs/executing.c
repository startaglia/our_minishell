#include "minishell.h"

void    executing(t_shell *shell, char **envp)
{
    int pid;

    if ((pid = fork()) < 0)
        return ;
    else if (!pid)
    {
        if (execve(shell->first_cmd_path, shell->execve_arg, envp) == - 1)
            return ;
    }
    close (pid);
    waitpid(pid, NULL, 0);
}
