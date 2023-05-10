#include "../includes/minishell.h"

void write_std_error(char *error)
{
    int i;

    i = -1;
    write(2, "Error: ", 7);
    while (error[++i])
        write(2, &error[i], 1);
}

void    print_error(int error)
{
    if (error == 1)
        write_std_error("could not get PWD\n");
    exit (error);
}