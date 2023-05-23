#include "../includes/minishell.h"

int ft_execredir(int red, t_shell *shell, char **cmd)
{
    int fd;
    int i;
    char *path;

    i = 0;
    while (cmd[i])
        i++;
    i--;
    if (!red)
        return (0);
    if (red == 4)
    {
        fd = open(cmd[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (fd < 0)
            return (1); //Fare uscita per bene.
        dup2(fd, STDOUT_FILENO);
        i = 0;
        while(ft_strncmp(cmd[i], ">", 1))
            i++;
        //printf("i vale : %d\n", i);
        char **newcmd = malloc(sizeof(char *) * i + 1);
        int k = 0;
        while(k<i)
        {
            newcmd[k] = ft_strdup(cmd[k]);
            //printf("NEWCMD : %s\n", newcmd[k]);
            k++;
        }
        newcmd[k] = NULL;
        if (ft_checkbuiltin(newcmd[0]))
            ft_exec_builtin(newcmd);
        else
        {
            //*QUI GESTISCO I COMANDI CHE IL SUB PERMETTE DI PRENDERE DAL BIN
            path = ft_findpath(newcmd[0]);
            //printf("%s\n", path);
            if (path != NULL)
                execute_cmd(path, newcmd, shell);
            else
                printf("Command not found: %s\n", newcmd[0]);
        }
        
    }
    return (0);
}