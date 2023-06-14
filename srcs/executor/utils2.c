/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:08:44 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/14 20:50:39 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_findvar(t_shell *shell, t_command *cmd)
{
    int     i;
    int     toskip;
    char    **tounset;
    char    **myvar;

    toskip = -1;
    i = 0;
    tounset = ft_split(cmd->split_cmd[1], 61);
    while (shell->copy_env[i])
    {
        myvar = ft_split(shell->copy_env[i], 61);
        if (!strcmp(myvar[0], tounset[0]))
            toskip = i;
        free_matrix(myvar);
        i++;
    }
    free_matrix(tounset);
    return(toskip);
}

int get_matrix_lenght(char **matrix)
{
    int i;

    i = 0;
    while (matrix[i])
        i++;
    return (i);
}