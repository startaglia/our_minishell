/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:27:42 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/19 00:22:19 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_authors(int	code)
{
	if (code == 4)
		printf("alpelliz -> github: \n");
	else if (code == 5)
		printf("startagl -> github: startaglia\n");
	else if (code == 6)
		printf("dcarassi -> github: DarkB0shy\n");
	else if (code == 7)
	{
		//sito per 3d art : https://textkool.com/   Font: ANSI Shadow
		//Codici colori ansii (Per chiudere il colore credo sia sempre \033[0m) https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
		// printf("\033[35m███████╗ ██████╗ █████╗ ███████╗████████╗ █████╗  ██████╗ ███╗   ██╗\033[0m\n");
		// printf("\033[35m██╔════╝██╔════╝██╔══██╗██╔════╝╚══██╔══╝██╔══██╗██╔════╝ ████╗  ██║\033[0m\n");
		// printf("\033[35m███████╗██║     ███████║███████╗   ██║   ███████║██║  ███╗██╔██╗ ██║\033[0m\n");
		// printf("\033[35m╚════██║██║     ██╔══██║╚════██║   ██║   ██╔══██║██║   ██║██║╚██╗██║\033[0m\n");
		// printf("\033[35m███████║╚██████╗██║  ██║███████║   ██║   ██║  ██║╚██████╔╝██║ ╚████║\033[0m\n");
		// printf("\033[35m╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝\033[0m\n");
		printf("\033[35mscastagn -> github: IamG-Root\033[0m\n");
	}
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
