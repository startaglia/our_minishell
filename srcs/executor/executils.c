/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:27:12 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/18 23:58:18 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_exec_bin(char **args, t_command *cmd, char **trimmed, char **env)
{
    char    *bin_path;

    bin_path = ft_findpath(args[0], env);
	if (cmd->infile >= 0 && bin_path != NULL)
    {
		if (execve(bin_path, trimmed, env) == -1)
            return (1);
        else
            return (0);
    }
	else
	{
		free(bin_path);
		free_matrix(trimmed);
		return (error(CMD_ERR, args[0]));
	}
}

int ft_actual_builtin(t_shell *shell, t_command *actual, t_list *first)
{
    if (!strcmp(actual->split_cmd[0], "cd"))
    {
		ft_cd(shell, actual);
        return (1);
    }
	else if(!strcmp(actual->split_cmd[0], "export"))
    {
    	ft_export(shell, actual);
        return (1);
    }
	else if(!strcmp(actual->split_cmd[0], "unset"))
    {
		ft_unset(shell, actual);
        return (1);
    }
	else if (!strcmp(actual->split_cmd[0], "exit"))
    {
		ft_exit(shell, first);
        return (1);
    }
    return (0);
}

int ft_prev_builtin(t_shell *shell, t_command *actual, t_command *prev, t_list *first)
{
    if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "cd"))
    {
		ft_cd(shell, prev);
        return (1);
    }
	else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "export"))
    {
		ft_export(shell, prev);
        return (1);
    }
	else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "unset"))
    {
		ft_unset(shell, prev);
        return (1);
    }
	else if (!strcmp(actual->cmd, "|") && !strcmp(prev->split_cmd[0], "exit"))
    {
		ft_exit(shell, first);
        return (1);
    }
    return (0);
}

int ft_exec_builtin(t_shell *shell, t_command *actual, t_command *prev, t_list *first)
{
    if (ft_actual_builtin(shell, actual, first))
        return (1);
    else if (ft_prev_builtin(shell, actual, prev, first))
        return (1);
    return (0);
}

t_command   *ft_run_list(t_shell *shell)
{
    t_command   *prev;

    while (shell->cmds_list->next &&
        strcmp(((t_command *)shell->cmds_list->content)->cmd, "|"))
    {
        prev = (t_command *)shell->cmds_list->content;
		shell->cmds_list = shell->cmds_list->next;
    }
    return (prev);
}