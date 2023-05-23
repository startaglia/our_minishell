#include "../../includes/minishell.h"

int ft_pwd()
{
    //*LA FUNZIONE GETCWD PRENDE IL PERCORSO ASSOLUTO DELLA DIRECTORY CORRENTE, VIENE CHIAMATA CON NULL E CON 0 COME ARGOMENTI. NULL SERVE AD ALLOCARE AUTOMATICAMENTE LA MEM NECESSARIA PER COPIARE LA PATH DELLA DIRECTORY CORRENTE, 0 SIGNIFICA CHE NON CI SONO RESTRIZIONI SULLA RICHIESTA.
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);

    // cwd = getcwd(NULL, 0);
	// printf("%s\n", cwd);
	// free(cwd);
    return (0);
}