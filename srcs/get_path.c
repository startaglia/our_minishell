#include "minishell.h"

int  mat_len(char **mat)
{
    int i;

    i = 0;
    if (!mat)
        return (0);
    while (mat[i])
        i++;
    return (i);
}

static char *create_path(char *cmd, char *paths)
{
    char    *ret;
    char    *dir;

    dir = ft_strjoin(paths, "/");
    ret = ft_strjoin(dir, cmd);
    free (dir);
    return (ret);
}

char    *get_path(char *cmd)
{
    char    **paths;
    char    *r_path;
    char    *path;
    int     i;

    i = -1;
    path = getenv("PATH");
    paths = ft_split(path, ':');
    while (paths[++i])
    {
        // if (paths[])
        //     return (NULL);
        // else
        // {
            r_path = create_path(cmd, paths[i]);
            // printf("%d\n", i);
            // printf("Path: %d\t%s\n", i, r_path);
            if (access(r_path, F_OK) == 0)
            {
                ft_free_matrix(paths);
                return (r_path);
            }
            else
            {
                free (r_path);
                if (i == 9)
                {
                    r_path = NULL;
                    break ;
                }
            }
        // }
    }
    if (!r_path)
        ft_free_matrix(paths);
    return (r_path);
}