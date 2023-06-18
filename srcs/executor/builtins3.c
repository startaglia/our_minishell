/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:27:42 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/14 22:18:36 by scastagn         ###   ########.fr       */
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
