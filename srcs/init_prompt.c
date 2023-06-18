/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:47 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/18 20:15:30 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_siginit(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

static void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
		return ;
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

static int	main_loop_2(t_shell *shell)
{
	t_list	*start;

	shell->pipe_words = ft_split_pipes(shell->line_to_split_exp, 124);
	shell->cmds = ft_add_pipes(shell->pipe_words);
	create_cmd_list(shell);
	start = shell->cmds_list;
	if (!((t_command *)shell->cmds_list->content)->split_cmd[0])
	{
		ft_free_list(start);
		ft_free_execve(shell);
		ft_free_shell(shell);
		return (1);
	}
	executorprova(shell);
	ft_free_list(start);
	ft_free_execve(shell);
	return (0);
}

static void	main_loop(t_shell *shell)
{
	while (1)
	{
		signal(SIGINT, handle_siginit);
		signal(SIGQUIT, handle_sigquit);
		shell->pipeline = readline(shell->prompt);
		if (!shell->pipeline)
			break ;
		if (check_syntax(shell->pipeline))
		{
			free(shell->pipeline);
			continue ;
		}
		shell->line_to_split = parsing(shell);
		shell->line_to_split_exp = expander(shell->line_to_split, shell);
		if (ft_strncmp(shell->pipeline, "", 1))
		{
			add_history(shell->pipeline);
			if (main_loop_2(shell))
				continue ;
		}
		ft_free_shell(shell);
	}
}

void	init_prompt(t_shell *shell, char **envp)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		user = "guest";
	init_values(&shell);
	shell->prompt = ft_strjoin(user, "@minishell$ ");
	ft_setenv(shell, envp);
	main_loop(shell);
	free(shell->prompt);
	free_matrix(shell->copy_env);
	free(shell);
}
