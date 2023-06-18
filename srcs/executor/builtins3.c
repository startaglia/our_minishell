/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:27:42 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/18 21:20:21 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell, t_list *start)
{
	if (ft_lstsize(start) > 2)
		return ;
	printf("exit\n");
	ft_free_shell(shell);
	ft_free_execve(shell);
	ft_free_list(shell->cmds_list);
	exit(0);
}

void	ft_builtin_ex(int builtin, char **trimmed, char **env)
{
	if (builtin == 1)
		ft_echo(trimmed);
	else if (builtin == 2)
		ft_pwd(env);
	else if (builtin == 3)
		ft_env(env);
	free_matrix(trimmed);
	exit(0);
}
