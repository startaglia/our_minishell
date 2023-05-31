/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:57:08 by startagl          #+#    #+#             */
/*   Updated: 2023/05/26 21:43:05 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		free_matrix(shell->pipe_words);
	}
}