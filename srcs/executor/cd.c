#include "../../includes/minishell.h"

int ft_cd(char **command)
{
    //* CHDIR CAMBIA LA DIRECTORY CORRENTE IN QUELLA CHE GLI PASSIAMO COME ARGOMENTO, DA NOTARE CHE LAVORA SOLO SULLA DIRECTORY CORRENTE E NON SU QUELLA DI ALTRI PROCESSI.
    if (chdir(command[1]) == -1)
        perror("Failed cd");
    return (0);
}