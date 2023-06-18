/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:27:12 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/18 21:33:19 by scastagn         ###   ########.fr       */
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