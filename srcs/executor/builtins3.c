/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi < dcarassi@student.42roma.it >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:27:42 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/19 11:58:34 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_authors(int code)
{
	if (code == 4)
		printf("\033[35malpelliz -> github: Beta-J23\033[0m\n");
	else if (code == 5)
		printf("\033[35mstartagl -> github: startaglia\033[0m\n");
	else if (code == 6)
		printf("\033[35mdcarassi -> github: DarkB0shy\033[0m\n");
	else if (code == 7)
		printf("\033[35mscastagn -> github: IamG-Root\033[0m\n");
}

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
	else if (builtin == 4)
		ft_authors(builtin);
	else if (builtin == 5)
		ft_authors(builtin);
	else if (builtin == 6)
		ft_authors(builtin);
	else if (builtin == 7)
		ft_authors(builtin);
	free_matrix(trimmed);
	exit(0);
}
