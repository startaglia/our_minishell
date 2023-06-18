/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:08:44 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/14 20:50:39 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_findvar(t_shell *shell, t_command *cmd)
{
	int		i;
	int		toskip;
	char	**tounset;
	char	**myvar;

	toskip = -1;
	i = 0;
	tounset = ft_split(cmd->split_cmd[1], 61);
	while (shell->copy_env[i])
	{
		myvar = ft_split(shell->copy_env[i], 61);
		if (!strcmp(myvar[0], tounset[0]))
			toskip = i;
		free_matrix(myvar);
		i++;
	}
	free_matrix(tounset);
	return (toskip);
}

void	ft_changevalue_2(char **copy_env, int i, char **newvar, char **myvar)
{
	char	*temp;

	free(myvar[1]);
	myvar[1] = ft_strdup(newvar[1]);
	free(copy_env[i]);
	temp = ft_strjoin(myvar[0], "=");
	copy_env[i] = ft_strjoin(temp, myvar[1]);
	free(temp);
	free_matrix(myvar);
	free_matrix(newvar);
}

void	ft_changevalue_3(char **copy_env, int i, char **newvar, char **myvar)
{
	char	*temp;

	free(copy_env[i]);
	free(myvar[0]);
	myvar[0] = strdup(newvar[0]);
	temp = ft_strjoin(myvar[0], "=");
	copy_env[i] = strdup(temp);
	free(temp);
	free_matrix(myvar);
	free_matrix(newvar);
}

void	trim_def_2(char *full, int *i, int *count)
{
	while (full[*i])
	{
		if (full[*i] == 61)
		{
			(*i)++;
			while (full[*i])
			{
				(*i)++;
				(*count)++;
			}
			break ;
		}
		(*i)++;
	}
}

char	*trim_def_3(char *full, int *i, int *count)
{
	char	*temp;

	*i = 0;
	*count = 0;
	trim_def_2(full, i, count);
	temp = malloc(sizeof(char) * (*count + 1));
	*i = 0;
	*count = 0;
	return (temp);
}
