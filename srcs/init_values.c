/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:30:10 by startagl          #+#    #+#             */
/*   Updated: 2023/06/04 15:40:17 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_mem(t_shell **shell)
{
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (!(*shell))
		return (1);
	/*
    	 shell->node = (t_node *)malloc(sizeof(t_node));
    	    if (!shell->node)
    	         return (1);
    	 shell->node->operators = (t_operators *)malloc(sizeof(t_operators));
    	     if (!shell->node->operators)
    	         return (1);*/
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
	(*shell)->cmds = NULL;
	return (0);
}