/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:01:18 by startagl          #+#    #+#             */
/*   Updated: 2023/05/10 13:01:58 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_in(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->pipeline[i])
	{
		if (shell->pipeline[i] == 34)
		{
			i++;
			while (shell->pipeline[i] != 34 && shell->pipeline[i + 1])
				i++;
		}
		if (shell->pipeline[i] == 39)
		{
			i++;
			while (shell->pipeline[i] != 39 && shell->pipeline[i + 1])
				i++;
		}
		if (shell->pipeline[i] == 60)
		{
			i++;
			if (shell->pipeline[i] == 60)
			{
				i++;
				if (shell->pipeline[i] == 60)
					return (std_error(IN));
				shell->sng_heredoc = true;
			}
			else
				shell->sng_in = true;
		}
		i++;
	}
	return (0);
}

int	check_out(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->pipeline[i])
	{
		if (shell->pipeline[i] == 34)
		{
			i++;
			while (shell->pipeline[i] != 34 && shell->pipeline[i + 1])
				i++;
		}
		if (shell->pipeline[i] == 39)
		{
			i++;
			while (shell->pipeline[i] != 39 && shell->pipeline[i + 1])
				i++;
		}
		if (shell->pipeline[i] == 62)
		{
			i++;
			if (shell->pipeline[i] == 62)
			{
				i++;
				if (shell->pipeline[i] == 62)
					return (std_error(OUT));
				shell->sng_append = true;
			}
			else
				shell->sng_redir = true;
		}
		i++;
	}
	return (0);
}