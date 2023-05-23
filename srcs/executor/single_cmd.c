#include "../includes/minishell.h"

int execute_cmd(char *path, char **cmd, t_shell *shell)
{
    pid_t pid;

    //*CREO UN PROCESSO PERCHÈ OGNI COMANDO CHE ESEGUO 'E DI FATTO UN PROCESSO
    pid = fork();
    if (pid < 0)
        perror("Pid error");
    if (pid == 0)
    {
        //* EXECVE ESEGUE UN COMANDO. PRENDE COME ARGOMENTI 1)LA PATH CHE SAREBBE IL PERCORSO COMPLETO DEL PROGRAMMA DA ESEGUIRE 2)UNA MATRICE DI ARGOMENTI CHE DEVE CONSIDERARE(!!CAPIRE SE 'E GIUSTO CHE GLI ARRIVI COME ARG[0]IL NOME DEL COMANDO!!) 3)UNA MATRICE CON TUTTE LE VARIABILI DI AMBIENTE CHE VERRANNO PASASTE AL NUOVO PROGRAMMA
        //* QUI DENTRO DI FATTO VENGONO ESEGUITI I COMANDI CHE SONO BUILTIN
        if (execve(path, cmd, shell->copy_env) == -1)
            perror("Error");
        close(pid);
    }
    else
    {
        close(pid);
        waitpid(pid, NULL, 0);
    }
    return (0);
}

char *ft_findpath(char *cmd)
{
    //* QUI CI SALVO TUTTO IL VALORE DELLA VAR DI AMBIENTE CHE SARA UNA ROBA TIPO /home/simone/.local/bin:/home/simone/bin:/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/home/simone/.dotnet/tools
    //*TUTTA QUESTA STRINGA CONTIENE UNA SERIE DI DIRECTORY SEPARATE DAI : E SONO UTILIZZATE COM PERCORSI DI RICERCA PER TROVARE ESEGUIBILI
    char *path;
    //* QUESTA E' LA PATH CORRETTA DELL'ESEGUIBILE, SE VIENE TROVATO
    char *right_path;
    //*QUESTA 'E MATRIX DELLA SPLIT FATTA SU PATH CON I :
    char **paths;
    int i;

    i = 0;
    path = getenv("PATH");
    paths = ft_split(path, ':');
    while(paths[i])
    {
        //*MI SERVE CREARE UNA STRINGA CHE ABBIA OGNI DIRECTORY CHE ERA NELLA VAR DI AMBIENTE PATH SEPARATA DAI : CON AGGIUNTO ALLA FINE /, PERCHE' SUBITO DOPO ANDRO' A CONTROLLARE SE IL COMMAND INSERITO HA GLI ACCESSI E QUINDI SE ESISTE. IN SOSTANZA CICLO SU OGNI DIRECTORY DEGLI ESEGUIBILI BIM E CONTROLLO SE IL COMANDO CHE HO SCRITTO E' UNO DI LORO.
        path = ft_strjoin(paths[i], "/");
        //* ALLA FINE DELLA PATH DEL MOMENTO, DOPO AVERCI MESSO IL / CI METTO ANCHE IL COMANDO CHE HO SCRITTO, SE LA DIR ESISTE CI ENTRA CON ACCESS E MI RITORNO LA PATH CHE CERCAVO.
        right_path = ft_strjoin(path, cmd);
        if (access(right_path, F_OK) == 0)
        {
            free(path);
            free_matrix(paths);
            return (right_path);
        }
        free(path);
        free(right_path);
        i++;
    }
    free_matrix(paths);
    return (NULL);
}

int exec_single_cmd(t_shell *shell)
{
    //* QUESTA 'E LA SPLIT DELLA STRINGA 
    char **cmd;
    //*QUI CI SALVO IL PERCORSO DEL COMANDO SE CI STA
    char *path;
    int i;
    int red;

    i = 0;
    //!PROVARE SE E' SUFFICIENTE SPLITTARE CON LO SPAZIO E BASTA, QUINDI FARE PROVE CON LE REDIRECTION
    cmd = ft_split(shell->pipeline, ' ');
    while(cmd[i])
    {
        //printf("%s\n", cmd[i]);
        //* TRIMMO TUTTI I SINGOLI E DOPPI APICI SE CI SONO ("" '') PERCHÈ TANTO E' IL COMPORTAMENTO CHE VOGLIO, BASH OPERA COME SE NON CI FOSSERO
        cmd[i] = ft_strtrim(cmd[i], "\"");
        cmd[i] = ft_strtrim(cmd[i], "'");
        i++;
    }
    // sta robba leakka da correggere.
    //*CONTROLLO SE HO SCRITTO EXIT. SE SCRIVO EXIT DEVO USCIRE DALLA MIA SHELL
    if (ft_strncmp(shell->pipeline, "exit", 4) == 0)
    {
        free_matrix(cmd);
        exit(0);
    }
    else
    {
        red = ft_checkredir(shell);
        if (!ft_execredir(red, shell, cmd))
        {
            //*CONTROLLO SE IL COMANDO 'E UN BUILTIN NON PERMESSO, CIO'E UNO DI QUELLI CHE DEVO COSTRUIRMI IO (ECHO, CD, PWD, EXPORT, UNSET, ENV, EXIT)
            if (ft_checkbuiltin(cmd[0]))
                ft_exec_builtin(cmd);
            else
            {
                //*QUI GESTISCO I COMANDI CHE IL SUB PERMETTE DI PRENDERE DAL BIN
                path = ft_findpath(cmd[0]);
                //printf("%s\n", path);
                if (path != NULL)
                    execute_cmd(path, cmd, shell);
                else
                    printf("Command not found: %s\n", cmd[0]);
            }
        }
        add_history(shell->pipeline);
        free_matrix(cmd);
    }
    return (0);
}
