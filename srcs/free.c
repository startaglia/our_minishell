/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:57:08 by startagl          #+#    #+#             */
/*   Updated: 2023/06/16 00:41:36 by scastagn         ###   ########.fr       */
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
	if (shell->line_to_split_exp)
		free(shell->line_to_split_exp);
}

void ft_free_execve(t_shell *shell)
{
	if (shell->cmds)
		free_matrix(shell->cmds);
	if (shell->pipe_words)
    	free_matrix(shell->pipe_words);
}

void ft_free_list(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		tmp = list->next;
		free(((t_command *)list->content)->cmd);
		free_matrix(((t_command *)list->content)->split_cmd);
		if (((t_command *)list->content)->heredoc)
			free(((t_command *)list->content)->heredoc);
		free(list->content);
		free(list);
		list = tmp;
	}
}