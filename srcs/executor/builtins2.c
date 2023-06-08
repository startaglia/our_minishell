/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:10:59 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/08 22:24:53 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    update_cwd(t_shell *shell)
{
    int     i;
    char    cwd[1024];

    i = 0;
    getcwd(cwd, sizeof(cwd));
    while (shell->copy_env[i])
    {
        if (!ft_strncmp("PWD=", shell->copy_env[i], 4))
        {
            free(shell->copy_env[i]);
            shell->copy_env[i] = ft_strjoin("PWD=", cwd);
        }
        i++;
    }
}