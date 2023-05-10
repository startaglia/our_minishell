#include "../includes/minishell.h"

int std_error(char *error)
{
    int i;

    i = 0;
    while (error[i])
        i++;
    return(write(2, error, i));
}

// void    print_error(int error)
// {
//     if (error == 1)
//         write_std_error("could not get PWD\n");
//     exit (error);
// }