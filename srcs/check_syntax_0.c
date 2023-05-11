#include "minishell.h"

static int  check_quotes(char *str)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (str[i])
    {
        if (str[i] == 34)
        {
            j++;
            i++;
            while (str[i] != 34 && str[i + 1])
                i++;
            if (str[i] == 34)
                j++;
        }
        else if (str[i] == 39)
        {
            k++;
            i++;
            while (str[i] != 39 && str[i + 1])
                i++;
            if (str[i] == 39)
                k++;
        }
        i++;
    }
    if (j % 2 != 0 || k % 2 != 0)
        return (1);
    return (0);
}

static int  check_and(char *str)
{
    int i;
    int check;

    i = 0;
    check = 0;
    while (str[i])
    {
        if (str[i] == 38)
        {
            i++;
            if (str[i] != 38)
            {
                check = 1;
                break ;
            }
        }
        i++;
    }
    return (check);
}

static int  check_pipes(char *str)
{
    int i;
    int check;

    check = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == 124)
        {
            i++;
            if (str[i] == 124)
            {
                i++;
                if (str[i] == 124)
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

int check_syntax(char *str)
{
    if (check_quotes(str))
        return (1);
    if (check_pipes(str))
        return (1);
    if (check_and(str))
        return (1);
    if (check_redirs(str))
        return (1);
    return (0);
}