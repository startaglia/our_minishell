/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:55:01 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/08 13:46:09 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
    t_shell shell;
    // int     i;

    // i = 0;
    // while (envp[i])
    // {
    //     if (!strncmp(envp[i], "OLDPWD", 6))
    //         printf("Trovato Daniele\n");
    //     i++;
    // }

    (void)argc;
    (void)argv;
    (void)envp;
    init_prompt(&shell, envp);
    return (0);
}