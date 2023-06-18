/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 22:16:32 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/18 22:56:44 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_set_files(t_command *actual)
{
    if (actual->outfile != 1)
    {
        dup2(actual->outfile, STDOUT_FILENO);
        close(actual->outfile);
    }
    if (actual->infile != 0)
    {
        dup2(actual->infile, STDIN_FILENO);
        close(actual->infile);
    }
}

void    ft_close_files(t_command *actual)
{
    if (actual->outfile != 1)
    {
        dup2(actual->copy_stdout, STDOUT_FILENO);
        close(actual->copy_stdout);
    }
    if (actual->infile != 0)
    {
        dup2(actual->copy_stdin, STDIN_FILENO);
        close(actual->copy_stdin);
    }
}

int ft_here_loop(t_command *actual, int *tmp, t_shell *shell)
{
    char    *line;
    while(1)
	{
		line = readline("> ");
		if (!line || !strcmp(line, actual->heredoc))
		{
			free(line);
			if (exec((actual->split_cmd), actual, *tmp, shell->copy_env))
				return (1);
			break;
		}
	}
    return (0);
}

int ft_first_last(t_command *actual, int *tmp, t_shell *shell)
{
    int pid;
    int child_status;
    
    pid = fork();
	if (!pid)
	{
        ft_set_files(actual);
		if (actual->heredoc)
            ft_here_loop(actual, tmp, shell);
		else
			if (exec((actual->split_cmd), actual, *tmp, shell->copy_env))
				return (1);
        ft_close_files(actual);
	}
	else
	{
		close(*tmp);
		while (waitpid(-1, &child_status, WUNTRACED) != -1);
		if (WIFEXITED(child_status))
			g_exit_status = WEXITSTATUS(child_status);
		*tmp = dup(0);
	}
    return (0);
}

int ft_pipe_cmd(t_command *prev, int *tmp, t_shell *shell)
{
    int fd[2];
    int pid;
    
    pipe(fd);
	pid = fork();
	if (!pid)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
        ft_set_files(prev);
		if (prev->heredoc)
            ft_here_loop(prev, tmp, shell);
		else
			if (exec(prev->split_cmd, prev, *tmp, shell->copy_env))
				return (1);
		ft_close_files(prev);
	}
	else
	{
		close(*tmp);
		close(fd[1]);
		*tmp = fd[0];
	}
    return (0);
}