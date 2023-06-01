/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:30:10 by startagl          #+#    #+#             */
/*   Updated: 2023/06/01 10:04:54 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static  int	init_mem(t_shell **shell)
{
	*shell = (t_shell *)malloc(sizeof(t_shell));
    if (!(*shell))
        return 1;
    // shell->node = (t_node *)malloc(sizeof(t_node));
    //    if (!shell->node)
    //         return (1);
    // shell->node->operators = (t_operators *)malloc(sizeof(t_operators));
    //     if (!shell->node->operators)
    //         return (1);
    return (0);  
}

int	init_values(t_shell **shell)
{
    if (!init_mem(shell))
        return (1);
    (*shell)->prompt = NULL;
    (*shell)->pipeline = NULL;
    (*shell)->line_to_split = NULL;
    (*shell)->pipe_words = NULL;
    (*shell)->copy_env = NULL;
    
    return (0);
}
