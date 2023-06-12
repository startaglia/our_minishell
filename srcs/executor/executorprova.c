/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executorprova.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:43:19 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/11 15:41:54 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *ft_findpath(char *cmd, char **env)
{
    char *path;
    char *right_path;
    char **paths;
    int i;

    i = 0;
    path = getpath(env);
    paths = ft_split(path, ':');
    while(paths[i])
    {
		free(path);
        path = ft_strjoin(paths[i], "/");
        right_path = ft_strjoin(path, cmd);
        if (access(right_path, F_OK) == 0)
        {
            free_matrix(paths);
            return (right_path);
        }
        free(right_path);
        i++;
    }
	free(path);
    free_matrix(paths);
	//free(path);
    return (NULL);
}

static int	error(char *str, char *err)
{
	while (*str)
		write(2, str++, 1);
	if (err)
		while (*err)
			write(2, err++, 1);
	write(2, "\n", 1);
	exit(1);
	return (1);
}

static int	exec(char **args, t_command *cmd, int fd, char **env)
{
    char	*bin_path;
	char	**trimmed;
	int		builtin;
    
	builtin = ft_is_builtin(args[0]);
	if (cmd->infile == 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	(void)fd;
	trimmed = ft_get_cmd(args);
	if (builtin)
	{
		if (builtin == 1)
			ft_echo(trimmed);
		else if (builtin == 2)
			ft_pwd(env);
		else if (builtin == 3)
			ft_env(env);
		bin_path = NULL;
		free_matrix(trimmed);
		exit(0);
	}
	else
	{
		bin_path = ft_findpath(args[0], env);
		if (bin_path != NULL && cmd->infile >= 0)
			execve(bin_path, trimmed, env);
		free(bin_path);
		free_matrix(trimmed);
		return (error("error: cannot execute ", args[0]));
	}
	//execve(bin_path, args, env);
	return (0);
}

int executorprova(t_shell *shell)
{
	int	pid;
	int	tmp;
	int	fd[2];
    t_command *prev;
	t_command *actual;

	pid = 0;
	tmp = dup(0);
	ft_set_redirs(shell);
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
		else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "cd"))
			ft_cd(shell, prev);
		else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "export"))
			ft_export(shell, prev);
		else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "unset"))
			ft_unset(shell, prev);
		else if (!strcmp(actual->split_cmd[0], "exit"))
			ft_exit(shell);
		else if (!strcmp(actual->split_cmd[0], "$?"))
		{
			printf("minishell: %d: command not found\n", exit_status);
			exit_status = 127;
		}
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
				// while (waitpid(-1, NULL, WUNTRACED) != -1)
				// 	;
				int child_status;

				while(waitpid(-1, &child_status, WUNTRACED) != -1)
					;
				if (WIFEXITED(child_status))
					exit_status = WEXITSTATUS(child_status);
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