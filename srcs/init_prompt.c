#include "../includes/minishell.h"

static void handle_siginit(int sig)
{
    if (sig == SIGINT)
    {
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
        rl_replace_line("", 0);
        rl_on_new_line();
    }
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

int main_loop(t_shell *shell, char **envp)
{
    while (1)
    {
        signal(SIGINT, handle_siginit);
        signal(SIGQUIT, handle_sigquit);
        shell->pipeline = readline(shell->prompt);
        if (shell->pipeline == NULL)
            exit (1);
        init_values(shell, envp);
        check_syntax(shell);
        if (!shell->pipe)
            exec_single_cmd(shell);
        if (ft_strncmp(shell->pipeline, "", 1))
        {
            add_history(shell->pipeline);
            if (parsing(shell))
                return (1);
            // shell->pipe_words = ft_split(shell->pipeline, ' ');
            // free(shell->pipe_words);
        }
        // free(shell->pipeline);
    }
    return (0);
}

int     init_prompt(t_shell *shell, char **envp)
{
    char    *user;

    user = getenv("USER");
    if (!user)
        user = "guest";
    shell->prompt = ft_strjoin(user, "@minishell$ ");
    main_loop(shell, envp);
    free(shell->prompt);
    return (0);
}