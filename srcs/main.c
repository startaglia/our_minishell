/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:55:01 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/17 15:31:16 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
    t_shell shell;

    (void)argc;
    (void)argv;
    (void)envp;
    init_prompt(&shell, envp);
    printf("exit\n");
    return (0);
}
