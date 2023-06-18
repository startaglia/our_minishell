/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:17:44 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/18 20:54:08 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_get_cmd(char **args)
{
	int		i;
	char	**trimmed;

	i = 0;
	while (args[i] && strcmp(args[i], ">") && strcmp(args[i], ">>")
		&& strcmp(args[i], "<") && strcmp(args[i], "<<"))
		i++;
	trimmed = (char **) malloc (sizeof(char *) * (i + 1));
	i = 0;
	while (args[i] && strcmp(args[i], ">") && strcmp(args[i], ">>")
		&& strcmp(args[i], "<") && strcmp(args[i], "<<"))
	{
		trimmed[i] = ft_strdup(args[i]);
		i++;
	}
	trimmed[i] = NULL;
	return (trimmed);
}

int	ft_set_out(char **cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	while (cmd[i])
	{
		if (!strcmp(cmd[i], ">"))
		{
			fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			i++;
		}
		else if (!strcmp(cmd[i], ">>"))
		{
			fd = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			i++;
		}
		i++;
	}
	return (fd);
}

int	ft_set_in(char **cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd[i])
	{
		if (!strcmp(cmd[i], "<"))
		{
			if (access(cmd[i + 1], F_OK) == 0)
				fd = open(cmd[i + 1], O_RDONLY);
			else
			{
				printf("Cannot open: %s\n", cmd[i + 1]);
				fd = -1;
			}
			i++;
		}
		i++;
	}
	return (fd);
}

void	ft_set_redirs(t_shell *shell)
{
	t_list	*temp;
	char	**space_splitted;

	temp = shell->cmds_list;
	while (temp)
	{
		space_splitted = ft_split_pipes(((t_command *)temp->content)->cmd, 32);
		((t_command *)temp->content)->outfile = ft_set_out(space_splitted);
		((t_command *)temp->content)->infile = ft_set_in(space_splitted);
		if (ft_find_heredoc(space_splitted))
			((t_command *)temp->content)->heredoc = ft_strdup(
					ft_find_heredoc(space_splitted));
		else
			((t_command *)temp->content)->heredoc = NULL;
		temp = temp->next;
		free_matrix(space_splitted);
	}
}

void	create_cmd_list(t_shell *shell)
{
	t_command	*element;
	int			i;

	i = 0;
	while (shell->cmds[i])
	{
		element = malloc(sizeof(t_command));
		element->cmd = ft_strdup(shell->cmds[i]);
		element->split_cmd = ft_split_pipes(element->cmd, 32);
		element->heredoc = NULL;
		element->infile = 1;
		element->outfile = 0;
		element->copy_stdout = dup(STDOUT_FILENO);
		element->copy_stdin = dup(STDIN_FILENO);
		if (i == 0)
			shell->cmds_list = ft_lstnew(element);
		else
			ft_lstadd_back(&(shell->cmds_list), ft_lstnew(element));
		i++;
	}
}
