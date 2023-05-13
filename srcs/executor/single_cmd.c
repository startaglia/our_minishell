#include "../includes/minishell.h"

int execute_cmd(char *path, char **cmd, t_shell *shell)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
        return (1);
    else if (!pid)
    {
        if (execve(path, cmd, shell->copy_env) == -1)
            return (printf("Error\n"));
    }
    close(pid);
    waitpid(pid, NULL, 0);
    return (0);
}

char *ft_findpath(char *cmd)
{
    char *path;
    char *right_path;
    char **paths;
    int i;

    i = 0;
    path = getenv("PATH");
    paths = ft_split(path, ':');
    while(paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        right_path = ft_strjoin(path, cmd);
        if (access(right_path, F_OK) == 0)
        {
            free(path);
            free_matrix(paths);
            return (right_path);
        }
        free(path);
        free(right_path);
        i++;
    }
    free_matrix(paths);
    return (NULL);
}

int exec_single_cmd(t_shell *shell)
{
    char **cmd;
    char *path;
    int i;

    i = 0;
    cmd = ft_split(shell->pipeline, ' ');

    if (ft_strncmp(cmd[0], "exit", 4) == 0)
    {
        while(cmd[i++])
            free(cmd[i]);
        free(cmd);
        exit(0);
    }
    else
    {
        path = ft_findpath(cmd[0]);
        //printf("La path giusta è : %s\n", path);
        execute_cmd(path, cmd, shell);
        free_matrix(cmd);
        // free(path);
    }
    return (0);
}