/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:27:42 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/09 22:32:01 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell)
{
	printf("exit\n");
	ft_free_shell(shell);
	ft_free_execve(shell);
	ft_free_list(shell->cmds_list);
	exit(0);
}
/*
int init_expander(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->copy_env[i])
		i++;
	shell->expander = malloc(sizeof(char) * i);
	return (0);
}
// pwd 
int		ft_expand(t_shell	*shell)
{
	int		i;

	i = 0;
	init_expander(shell);

	while(shell->copy_env)
	{
		

	}

}*/