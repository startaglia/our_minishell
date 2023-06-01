/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:57:08 by startagl          #+#    #+#             */
/*   Updated: 2023/06/01 11:55:54 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	check_mem(t_shell *shell)
// {
	
// 	return (0);
// }


int	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if(!matrix)
		return (1);
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (0);
}

void ft_free_shell(t_shell *shell)
{
	if (shell != NULL)
	{
		free(shell->prompt);
		free(shell->pipeline);
		free(shell->line_to_split);
		free_matrix(shell->copy_env);
		free_matrix(shell->pipe_words);
	}
}
