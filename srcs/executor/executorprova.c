/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executorprova.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:43:19 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/18 21:36:14 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_findpath(char *cmd, char **env)
{
    char *path;
    char *right_path;
    char **paths;
    int i;

    i = 0;
    path = getpath(env);
	if (!path)
		return (NULL);
    paths = ft_split(path, ':');
    while(paths[i++])
    {
		free(path);
        path = ft_strjoin(paths[i], "/");
        right_path = ft_strjoin(path, cmd);
        if (access(right_path, F_OK) == 0)
        {
			ft_free_paths(path, paths);
            return (right_path);
        }
        free(right_path);
    }
	ft_free_paths(path, paths);
    return (NULL);
}

static int	exec(char **args, t_command *cmd, int fd, char **env)
{
	char	**trimmed;
	int		builtin;
    
	builtin = ft_is_builtin(args[0]);
	if (cmd->infile == 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	trimmed = ft_get_cmd(args);
	trimmed = ft_strtrim_all(trimmed);
	if (access(trimmed[0], F_OK) == 0)
	{
		if (cmd->infile >= 0)
			execve(trimmed[0], trimmed, env);
	}
	if (builtin)
		ft_builtin_ex(builtin, trimmed, env);
	else
		return (ft_exec_bin(args, cmd, trimmed, env));
	return (0);
	//execve(bin_path, args, env);
}

int executorprova(t_shell *shell)
{
	int			pid;
	int			tmp;
	int			fd[2];
	int			child_status;
    t_command	*prev;
	t_command	*actual;
	t_list		*first;

	pid = 0;
	tmp = dup(0);
	ft_set_redirs(shell);
	first = shell->cmds_list;
	while (shell->cmds_list)
	{
		while (shell->cmds_list->next && strcmp(((t_command *)shell->cmds_list->content)->cmd, "|"))
        {
            prev = (t_command *)shell->cmds_list->content;
			shell->cmds_list = shell->cmds_list->next;
        }
		actual = (t_command *)shell->cmds_list->content;
		if (!strcmp(actual->split_cmd[0], "cd"))
			ft_cd(shell, actual);
		else if(!strcmp(actual->split_cmd[0], "export"))
			ft_export(shell, actual);
		else if(!strcmp(actual->split_cmd[0], "unset"))
			ft_unset(shell, actual);
		else if (!strcmp(actual->split_cmd[0], "exit"))
			ft_exit(shell, first);
		else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "cd"))
			ft_cd(shell, prev);
		else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "export"))
			ft_export(shell, prev);
		else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "unset"))
			ft_unset(shell, prev);
		else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "exit"))
			ft_exit(shell, first);
		else if (shell->cmds_list->next == NULL)
		{
			pid = fork();
			if (!pid)
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
				if (actual->heredoc)
				{
					char *line;
					while(1)
					{
						line = readline("> ");
						if (!line || !strcmp(line, actual->heredoc))
						{
							free(line);
							if (exec((actual->split_cmd), actual, tmp, shell->copy_env))
								return (1);
							break;
						}
					}
				}
				else
					if (exec((actual->split_cmd), actual, tmp, shell->copy_env))
						return (1);
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
			else
			{
				close(tmp);
				while (waitpid(-1, &child_status, WUNTRACED) != -1);
				if (WIFEXITED(child_status))
					g_exit_status = WEXITSTATUS(child_status);
				tmp = dup(0);
			}
            break;
		}
		else if (!strcmp(((t_command *)shell->cmds_list->content)->cmd, "|"))
		{
			pipe(fd);
			pid = fork();
			if (!pid)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
				if (prev->outfile != 1)
				{
					dup2(prev->outfile, STDOUT_FILENO);
					close(prev->outfile);
				}
				if (prev->infile != 0)
				{
					dup2(prev->infile, STDIN_FILENO);
					close(prev->infile);
				}
				if (prev->heredoc)
				{
					char *line;
					while(1)
					{
						line = readline("> ");
						if (!line || !strcmp(line, prev->heredoc))
						{
							free(line);
							if (exec((prev->split_cmd), prev, tmp, shell->copy_env))
								return (1);
							break;
						}
					}
				}
				else
					if (exec(prev->split_cmd, prev, tmp, shell->copy_env))
						return (1);
				if (prev->outfile != 1)
				{
					dup2(prev->copy_stdout, STDOUT_FILENO);
					close(prev->copy_stdout);
				}
				if (prev->infile != 0)
				{
					dup2(prev->copy_stdin, STDIN_FILENO);
					close(prev->copy_stdin);
				}
			}
			else
			{
				close(tmp);
				close(fd[1]);
				tmp = fd[0];
			}
		}
        shell->cmds_list = shell->cmds_list->next;
	}
	close(tmp);
	return (0);
}