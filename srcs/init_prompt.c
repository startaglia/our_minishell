#include "../includes/minishell.h"

static void handle_siginit(int sig)
{
    if (sig == SIGINT)
    {
        //* AL RICEVIMENTO DEL SEGNATE SIGINT CON IOCTL MANDO INVIO UN CARATTERE DI NUOVA RIGA \n SULLO STANDARD INPUT (STDIN_FILENO); TIOCISTI SERVE A SIMULARE L'EFFETTO IMMEDIATO DI UNA NUOVA RIGA DOPO AVER PREMUTO CTRL +C (SEGNALE SIGINT)
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
        //* REPLACE LINE SOSTITUISCE LA LINEA CORRENTE CON UNA STRINGA VUOTA IN QUESTO CASO, IN PRATICA OGNI VOLTA CHE PREMO CTRL+C MI COMPARE QUELLO CHE C'E' SU REPLACE LINE
        rl_replace_line("", 0);
        //* PIU O MENO FA LA STESSA COSA DI IOCTL, NELLO SPECIFICO SPOSTA IL CURSORE SU UNA NUOVA LINEA DEL TERMINALE
        rl_on_new_line();
    }
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
    //*QUESTA PUNTA LA RIGA DI COMANDO ALLA POSIZIONE CORRENTE DEL CURSORE
	rl_redisplay();
}

int main_loop(t_shell *shell, char **env)
{
    while (1)
    {
        //!PER TUTTI E DUE I SEGNALI NON HO BEN CAPITO L' UTILITA' DI ALCUNE CHIAMATE ALLE FUNZIONI. VANNO ACCETTATE COSI E BASTA. TIPO SE SIGQUIT LA COMMENTO FUNZIONE TUTTO ALLO STESSO MODO
        //*CRTL+C
        signal(SIGINT, handle_siginit);
        //*CRTL+\*
        signal(SIGQUIT, handle_sigquit);
        shell->pipeline = readline(shell->prompt);
        if (shell->pipeline == NULL)
            exit (1);
        if (check_syntax(shell))
            continue ;
        init_values(shell, env);
        //! CHECK SINTAX MODIFICA IL VALORE DI SHELL->PIPE SE LA TROVA, PERO' INIT VALUE LO METTE UGUALE A 0 DI DEFAULT, CAPIRE SE SERVE TOGLIERLO DA CHECKSINTAX

        //* SE NON C'È UNA PIPE VUOL DIRE CHE C'È SOLO UN COMANDO QUINDI NON SERVE PROPRIO ENTRARE DENTRO LA CONDIZIONE SUCCESSIVA. 
        if (!shell->pipe)
            exec_single_cmd(shell);
        if (ft_strncmp(shell->pipeline, "", 1))
        {
            add_history(shell->pipeline);
            shell->line_to_split = parsing(shell);
            if (shell->line_to_split == NULL)
                return (1);
            shell->pipe_words = ft_split(shell->line_to_split, 32);
            //printf("PARSING %s\n", shell->line_to_split);
            // int i = -1;
            // while (shell->pipe_words[++i])
            //     printf("SPLIT: %s\n", shell->pipe_words[i]);
            create_instruction_list(shell);
            free(shell->pipe_words);
            free(shell->line_to_split);
        }
        // free(shell->pipeline);
    }
    return (0);
}

int     init_prompt(t_shell *shell, char **env)
{
    char    *user;
    //* LA FUNZIONE GET ENV OTTIENE IL VALORE DELLE VARIABILI DI AMBIENTE, IN QUESTO CASO STO PRENDENDO IL VALORE DELLA VARIABILE USER CHE CONTIENE IL NOME DELL' UTENTE CORRENTE.
    user = getenv("USER");
    if (!user)
        user = "guest";
    shell->prompt = ft_strjoin(user, "@minishell$ ");
    main_loop(shell, env);
    free(shell->prompt);
    return (0);
}