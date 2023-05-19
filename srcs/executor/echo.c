#include "../../includes/minishell.h"

int ft_echo(char **command)
{
    int i;

    i = 1;
    //* CONTROLLO SE IL PRIMO COMANDO 'E UNA FLAG -N ('E DA GESTIRE, SE CE -N LA LINEA DI PRINTF VIENE STAMPATA DIRETTAMENTE ATTACCATA ALLA LINEA DI PROMPT SUCCESSIVA), INVECE DI ECHO METTE UN \n
    if (ft_strncmp(command[1], "-n", 2) == 0)
        i++;
    while (command[i])
    {
        printf("%s", command[i]);
        //*QUI CONTROLLO SE NON 'E L'ULTIMA PAROLA DELLA STRINGA CHE VOGLIO STAMPARE CON ECHO ALLORA CI METTO UNA SPAZIO, SE NON FACESSI COSI MI STAMPREBBE TUTTE LE PAROLE ATTACCATE
        if (command[i + 1])
            printf(" ");
        i++;
    }
    // printf("%s\n", command[1]);
    //*SE C'E IL -n RITORNA SUBITO, ALTRIMENTI PRIMA METTI UN NEWLINE POI RITORNA
    if (ft_strncmp(command[1], "-n", 2) == 0)
        return (0);
    else
        printf("\n");
    return (0);
}