// COME RIDIREZIONARE L'OUT: PER APPEND FLAG (O_APPEND) INVECE DI (O_TRUNC)

fd = open("file.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
copy_stdout = dup(STDOUT_FILENO);
dup2(fd, STDOUT_FILENO);
close(fd);
executor(shell);
dup2(copy_stdout, STDOUT_FILENO);
close(copy_stdout);


// COME RIDIREZIONARE L'IN

if (access("file.txt", F_OK) == 0)
            {
                fd = open("file.txt", O_RDONLY);
                copy_stdin = dup(STDIN_FILENO);
                dup2(fd, STDIN_FILENO);
                close(fd);
                executor(shell);
                dup2(copy_stdin, STDIN_FILENO);
                close(copy_stdin);
            }


// COME FARE L'HEREDOC

char *limiter = "limiter";
            char *line;
            while(1)
            {
                line = readline("> ");
                if (!line || !strcmp(line, limiter))
                {
                    free(line);
                    executor(shell);
                    break;
                }
            }


//TO_FIX:

0.0     SE SU BASH FAI EXIT E DAI UN ALTRO ARGOMENTO, AD ESEMPIO PWD DA QUESTO OUT E POI ESCE
            exit
            bash: exit: pwd: numeric argument required
0.1     SE SI STAMPA echo "$PWD" '$USER' STAMPA SOLO IL PWD, COSI COME SE FACCIO echo '$PWD' "$USER" STAMPA SOLO USER.
        BASH STAMPA IL VALORE DI QUELLO SI TROVA TRA DOUBLE QUOTES E IL NOME DELLA VARIABILE DI QUELLO CHE SI TROVA TRA SINGLEQUOTES.
0.2     SE SI FA UN EXPORT CON UN UGUUALE E BASTA DI UNA VARIABILE CHE GIA ESISTE VA IN SEGFAULT
        AD ESEMPIO SE SI MANDA export PWD= VA IN SEG.
0.3     RUNNANDO $? L'EXIT STATUS É 0 O 127, IL NOSTRO STAMPA 0 O 1. ANCHE IL MESSAGGIO DI ERRORE É LEGGERMENTE DIVERSO
        IL NOSTRO STAMPA error: cannot execute 1  BASH STAMPA 127: command not found
0.4     SE RUNNO 'bin/ls' BASH STAMPA COMUNQUE LS, IL NOSTRO CI DICE CHE NON TROVA BIN, LS. SI CORREGGE FACENDO UNA TRIM DEI SINGOLI
        E DOPPI APICI DENTRO A EXEC
0.5     SE RUNNO 'bin/asdasdasd' IL MESSAGGIO DI ERRORE É DIVERSO, IL NOSTRO STAMPA error: cannot execute '/bin/asdasdasd'
        BASH STAMPA bash: /bin/dsasdadsa: No such file or directory
0.6     SE MANDO IL SEGNALE CTRL \ RISTAMPA UN PROMPT SULLA STESSA LINEA, BASH NON FA NULLA, NEANCHE RISTAMPARE IL PROMPT
0.6     SE MANDO IL SEGNALE CTRL D IL NOSTRO ESCE SENZA SCRIVERE EXIT, BASH ESCE SCRIVENDO EXIT
0.7     SE MANDO echo '' IL NOSTRO STAMPA SOLO UNA SINGLE QUOTE, BASH STAMPA UNA LINEA VUOTA
0.8     SE MANDO echo "" IL NOSTRO STAMPA SOLO UNA DOUBLE QUOTE, BASH STAMPA UNA LINEA VUOTA
0.9     SE CREO AD ESEMPIO export GEGE COSI SENZA NIENTE IL NOSTRO LA CREA, BASH LA CREA SOLO SE CI SI METTE ALMENO UN UGUALE ESEMPIO
        export GEGE= BASH LA CREA, IL NOSTRO CREA QUALSIASI COSA.
1.0     RIVEDERE L'HEREDOC:
            gestire  questo caso=> echo dio << echo banana
            deve printare "dio banana"

            fare tanti test con il comando "cat" che ad ora fa il panico che si aspetta
            comandi in input nonostante venga scritto il delimiter

            gestire bene i segnali con il control+C dove dovrebbe chiudere il prompt
                apre un altro prompt (maybe problemi con i processi?)
            && con control+D dovrebbe sempre chiudere ma lanciando il comando (in teoria questo gia lo fa)
                (easy)
1.1     SE NELLE PIPES SI ESEGUE AD ESEMPIO 123456789 | echo ciao DA OUTPUT DIVERSI OGNI VOLTA
                startagl@minishell$ 123456789 | echo ciao
                error: cannot execute ciao 
                123456789
                startagl@minishell$ 123456789 | echo ciao
                error: cannot execute 123ciao 
                456789
                startagl@minishell$ 123456789 | echo ciao
                error: cannot execute 123ciao 
                456789
                startagl@minishell$ 123456789 | echo ciao
                error: cannot execute 12ciao 
                3456789
                startagl@minishell$ 123456789 | echo ciao
                error: cannot execute 123456ciao 
                789
                startagl@minishell$ 123456789 | echo ciao
                error: cannot execute 123ciao 
                456789
                startagl@minishell$ 123456789 | echo ciao
                error: cannot execute 12ciao 
                3456789
        STESSA COSA SE LO SI DA CON DUE PIPE
                startagl@minishell$ 123456789 | ABCDEFGH | echo ciao
                error: cannot execute 123456789
                error: cannot execute ABCDEFGHciao 

                startagl@minishell$ 123456789 | ABCDEFGH | echo ciao
                error: cannot execute 123456789
                error: cannot execute ABCDEciao 
                FGH
                startagl@minishell$ 123456789 | ABCDEFGH | echo ciao
                error: cannot execute 123456789
                error: cannot execute ABCDEFGH
                ciao 
                startagl@minishell$ 123456789 | ABCDEFGH | echo ciao
                error: cannot execute 123456789
                error: cannot execute ABCDEFGH
                ciao
1.2     SE LANCIO echo ($USER) IL NOSTRO PRINTA SOLO UNA PARENTESI, BASH INVECE PRINTA UN ERRORE
                startagl@e4r6p4:~/Desktop/i_shell$ echo ($USER)
                bash: syntax error near unexpected token `$USER'



