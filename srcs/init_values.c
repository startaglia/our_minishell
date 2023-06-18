/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:30:10 by startagl          #+#    #+#             */
/*   Updated: 2023/06/17 13:21:53 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	init_mem(t_shell **shell)
{
	*shell = (t_shell *)malloc(sizeof(t_shell));
	if (!(*shell))
		return (1);
	return (0);
}

int	init_values(t_shell **shell)
{
	if (!init_mem(shell))
		return (1);
	(*shell)->prompt = NULL;
	(*shell)->pipeline = NULL;
	(*shell)->line_to_split = NULL;
	(*shell)->line_to_split_exp = NULL;
	(*shell)->pipe_words = NULL;
	(*shell)->copy_env = NULL;
	return (0);
}

int	get_matrix_lenght(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	ft_setenv(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->copy_env = malloc (sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		shell->copy_env[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->copy_env[i] = NULL;
}
