/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:47 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/01 15:12:14 by startagl         ###   ########.fr       */
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
        {
            printf("exit\n");
            break ;
        }
        if(check_syntax(shell->pipeline))
            return ;
        shell->line_to_split = parsing(shell);
        if (ft_strncmp(shell->pipeline, "", 1))
        {
            add_history(shell->pipeline);
            if (shell->line_to_split == NULL)
                break ;
            shell->pipe_words = ft_split(shell->line_to_split, 32);
            executor(shell);   
            free_matrix(shell->pipe_words);
        }
        free(shell->pipeline);
        free(shell->line_to_split);
    }
}

void    init_prompt(t_shell *shell, char **envp)
{
    char    *user;
    int     i;

    i =  0;
    user = getenv("USER");
    if (!user)
        user = "guest";
    init_values(&shell);
    shell->prompt = ft_strjoin(user, "@minishell$ ");
    while(envp[i])
        i++;
    shell->copy_env = (char **)malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (envp[i])
    {
        shell->copy_env[i] = ft_strdup(envp[i]);
        i++;
    }
    shell->copy_env[i] =  NULL; 
    main_loop(shell);
    free(shell->prompt);
    free(shell);
}
