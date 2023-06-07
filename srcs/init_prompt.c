/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:47 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/07 12:02:28 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void main_loop(t_shell *shell)
{
    t_list  *start;

    while (1)
    {
        signal(SIGINT, handle_siginit);
        signal(SIGQUIT, handle_sigquit);
        shell->pipeline = readline(shell->prompt);
        if (!shell->pipeline)
            break ;
        check_syntax(shell->pipeline);
        shell->line_to_split = parsing(shell);
        if (ft_strncmp(shell->pipeline, "", 1))
        {
            add_history(shell->pipeline);
            if (shell->line_to_split == NULL)
                break ;
            shell->pipe_words = ft_split_pipes(shell->line_to_split, 124);
            shell->cmds = ft_add_pipes(shell->pipe_words);
            create_cmd_list(shell);
            start = shell->cmds_list;
            executorprova(shell);
            ft_free_list(start);
        }
        ft_free_shell(shell);
    }
}

void init_prompt(t_shell *shell, char **envp)
{
    char    *user;

    user = getenv("USER");
    if (!user)
        user = "guest";
    init_values(&shell);
    shell->prompt = ft_strjoin(user, "@minishell$ ");
    shell->copy_env = envp;
    main_loop(shell);
    free(shell->prompt);
    free(shell);
}