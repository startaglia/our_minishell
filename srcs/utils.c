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