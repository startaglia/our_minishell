/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:57:08 by startagl          #+#    #+#             */
/*   Updated: 2023/06/06 21:55:46 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if(!matrix)
		return (1);
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (0);
}

void ft_free_shell(t_shell *shell)
{
	if (shell->pipeline)
		free(shell->pipeline);
	if (shell->line_to_split)
    	free(shell->line_to_split);
	if (shell->line_to_split_expand != NULL)
		free(shell->line_to_split_expand);
}

void ft_free_list(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		tmp = list->next;
		// if (list->content != NULL)
		// 	free(list->content);
		// if (list != NULL)
		// 	free(list);
		// if (((t_command *)list->content)->cmd != NULL)
		// 	free(((t_command *)list->content)->cmd);
		// if (((t_command *)list->content)->split_cmd != NULL)
		// 	free_matrix(((t_command *)list->content)->split_cmd);
		// if (((t_command *)list->content)->heredoc != NULL)
		// 	free(((t_command *)list->content)->heredoc);
		list = tmp;
	}
}

void	ft_free_execve(t_shell *shell)
{
	if (shell->cmds)
		free_matrix(shell->cmds);
	if (shell->pipe_words)
    	free_matrix(shell->pipe_words);
}