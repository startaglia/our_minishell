/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executorprova.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:43:19 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/18 23:42:13 by scastagn         ###   ########.fr       */
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

int	exec(char **args, t_command *cmd, int fd, char **env)
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
}

int executorprova(t_shell *shell)
{
	int			tmp;
    t_command	*prev;
	t_command	*actual;
	t_list		*first;

	tmp = dup(0);
	ft_set_redirs(shell);
	first = shell->cmds_list;
	while (shell->cmds_list)
	{
		prev = ft_run_list(shell);
		actual = (t_command *)shell->cmds_list->content;
		if (ft_exec_builtin(shell, actual, prev, first));
		else if (shell->cmds_list->next == NULL)
		{
			ft_first_last(actual, &tmp, shell);
            break;
		}
		else if (!strcmp(((t_command *)shell->cmds_list->content)->cmd, "|"))
			ft_pipe_cmd(prev, &tmp, shell);
        shell->cmds_list = shell->cmds_list->next;
	}
	close(tmp);
	return (0);
}