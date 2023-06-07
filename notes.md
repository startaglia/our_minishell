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