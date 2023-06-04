/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:17:44 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/04 20:34:29 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void create_cmd_list(t_shell *shell)
{
    t_command   *element;
    int         i;

    i = 0;
    while (shell->cmds[i])
    {
        element = malloc(sizeof(t_command));
        element->cmd = ft_strdup(shell->cmds[i]);
        element->split_cmd = ft_split(element->cmd, 32);
        element->infile = 0;
        element->outfile = 0;
        element->copy_stdout = dup(STDOUT_FILENO);
        element->copy_stdin = dup(STDIN_FILENO);
        if (i == 0)
            shell->cmds_list = ft_lstnew(element);
        else
            ft_lstadd_back(&(shell->cmds_list), ft_lstnew(element));
        i++;
    }
}