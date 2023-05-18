#include "../includes/minishell.h"

int execute_cmd(char *path, char **cmd, t_shell *shell)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
        perror("Pid error");
    if (pid == 0)
    {
        if (execve(path, cmd, shell->copy_env) == -1)
            perror("Error");
        close(pid);
    }
    else
    {
        close(pid);
        waitpid(pid, NULL, 0);
    }
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
    while(cmd[i])
    {
        //printf("%s\n", cmd[i]);
        cmd[i] = ft_strtrim2(cmd[i], 34);
        cmd[i] = ft_strtrim2(cmd[i], 39);
        i++;
    }
    // sta robba leakka da correggere.
    if (ft_strncmp(shell->pipeline, "exit", 4) == 0)
    {
        // while(cmd[i--])
        //     free(cmd[i]);
        // free(cmd);
        // //free(shell->pipeline);
        free_matrix(cmd);
        exit(0);
    }
    else
    {
        if (ft_checkbuiltin(cmd[0]))
            ft_exec_builtin(cmd);
        else
        {
            path = ft_findpath(cmd[0]);
            //printf("%s\n", path);
            if (path != NULL)
                execute_cmd(path, cmd, shell);
            else
                printf("Command not found: %s\n", cmd[0]);
        }
        free_matrix(cmd);
    }
    return (0);
}