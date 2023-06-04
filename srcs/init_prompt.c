/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:47 by scastagn          #+#    #+#             */
/*   Updated: 2023/05/26 22:10:20 by scastagn         ###   ########.fr       */
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
    while (1)
    {
        signal(SIGINT, handle_siginit);
        signal(SIGQUIT, handle_sigquit);
        shell->pipeline = readline(shell->prompt);
        if (!shell->pipeline)
        // {
            // printf("PRIMO BREAK\n");
            // break ;
            return ;
        // }
        if(check_syntax(shell->pipeline))
            return ;
        shell->line_to_split = parsing(shell);
        if (ft_strncmp(shell->pipeline, "", 1))
        {
            add_history(shell->pipeline);
            // if (shell->line_to_split == NULL)
            // {
            // printf("SEC BREAK\n");

            //     break ;
            // }
            shell->pipe_words = ft_split(shell->line_to_split, 32);
            // "ls -la | cose" ha comportamenti strani, poi quando scrivi un comando che non riesce ad eseguire
            // N volte bisogna premere N volte CTRL+D per uscire dal loop infernale
            executor(shell);
            free_matrix(shell->pipe_words);
        }
    free(shell->pipeline);
	free(shell->line_to_split);
	// free_matrix(shell->pipe_words);
    // free(shell->pipe_words);
    }
    // free(shell);
}

void    init_prompt(t_shell *shell, char **envp)
{
    char    *user;
    char    *tmp;

    tmp = "\n";
    user = getenv("USER");
    if (!user)
        user = "\nguest";
    user = ft_strjoin(tmp, user);
    init_values(shell);
    shell->prompt = ft_strjoin(user, "@minishell$ ");
    free(user);
    shell->copy_env = envp;
    main_loop(shell);
    // printf("sono uscito dal loop infernale\n");
    //free(shell);
}