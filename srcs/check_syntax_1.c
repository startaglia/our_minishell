#include "minishell.h"

static int  check_redir(char *str, int dir)
{
    int i;
    int check;

    check = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == dir)
        {
            i++;
            if (str[i] == dir)
            {
                i++;
                if (str[i] == dir)
                {
                    check = 1;
                    break ;
                }
            }
        }
        i++;
    }
    return (check);
}

int check_redirs(char *str)
{
    if (check_redir(str, '<'))
        return (1);
    if (check_redir(str, '>'))
        return (1);
    return (0);
}