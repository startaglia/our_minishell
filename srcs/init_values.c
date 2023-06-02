/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:30:10 by startagl          #+#    #+#             */
/*   Updated: 2023/05/26 21:26:05 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_mem(t_shell *shell)
{
    (void)shell;
	// shell = (t_shell *) malloc(sizeof(t_shell));
    //     if (!shell)
    //         return (1); 
    // shell->node = (t_node *)malloc(sizeof(t_node));
    //    if (!shell->node)
    //         return (1);
    // shell->node->operators = (t_operators *)malloc(sizeof(t_operators));
    //     if (!shell->node->operators)
    //         return (1);
    printf("No need\n");
    return (0);  
}

int	init_values(t_shell *shell)
{
    if (!init_mem(shell))
        return (1);
    return (0);
}