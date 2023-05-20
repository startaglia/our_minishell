#include "minishell.h"

static void main_loop(t_shell *shell, char **envp)
{
    (void)envp;
    signal(SIGINT, ft_sig_handel);
    signal(SIGQUIT, ft_sig_handel);
    while (1)
    {
        shell->pipeline = readline(shell->prompt);
        if (!shell->pipeline)
            break ;
        if (ft_strncmp(shell->pipeline, "", 1))
        {
            add_history(shell->pipeline);
            if (!check_syntax(shell->pipeline))
            {
                get_first_command_path(shell);
                if (!shell->first_cmd_path)
                    write_std_error("command not found\n");
                else
                {
                    free(shell->execve_arg);
                    free(shell->first_cmd_path);
                    free_nodes(shell->token);
                    // executing(shell, envp);
                }
            }
            free(shell->pipeline);
            free(shell->line_to_split);
            free(shell->splitted_pipe);
        }
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
    shell->first_cmd_path = NULL;
    get_pwd(shell);
    main_loop(shell, envp);
    free(shell->prompt);
}
