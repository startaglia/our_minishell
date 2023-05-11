#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
    ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

static void main_loop(t_shell *shell, char **envp)
{
    // char *echo_cmd[] = {"echo", "ciao", NULL};
    char    *right_path;

    while (1)
    {
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);
        shell->pipeline = readline(shell->prompt);
        if (!shell->pipeline)
            break ;
        // if (ft_strncmp(shell->pipeline, "echo", 4))
        // {
        //     int pid;
        //     if ((pid = fork()) < 0)
        //         return ;
        //     else if (!pid)
        //         execvp("/bin/echo", echo_cmd);
        //     close(pid);
        //     waitpid(pid, NULL, 0);
        // }
        if (ft_strncmp(shell->pipeline, "", 1))
        {
            add_history(shell->pipeline);
            if (!check_syntax(shell->pipeline))
            {
                shell->splitted_pipe = ft_split(shell->pipeline, ' ');
                right_path = get_path(shell->splitted_pipe[0])
                if (right_path)
                {
                    // if (execve())
                    printf("dio ultra porco\n");
                }
            }
        } 
        free(shell->pipeline);
    }
}

static void  get_pwd(t_shell *shell)
{
    char    *home;
    char    *temp;

    shell->prompt = "\n$";
    home = getenv("PWD");
    if (!home)
        print_error(1);
    temp = getenv("USER");
    if (!temp)
        temp = "guest";
    temp = ft_strjoin(temp, "@minishell-");
    temp = ft_strjoin(temp, home);
    shell->prompt = ft_strjoin(temp, shell->prompt);
    free(temp);
}

void init_prompt(t_shell *shell, char **envp)
{
    get_pwd(shell);
    main_loop(shell);
    free(shell->prompt);
}
