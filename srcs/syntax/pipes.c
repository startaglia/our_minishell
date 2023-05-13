/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:35:59 by startagl          #+#    #+#             */
/*   Updated: 2023/05/10 13:02:48 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipes(t_shell *shell)
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
		if (shell->pipeline[i] == 124)
		{
			i++;
			if (shell->pipeline[i] == 124)
			{
				i++;
				if (shell->pipeline[i] == 124)
					return (std_error(PIP));
			}
			else
			{
				//shell->node->operators->pipe = true; //non funge non so perchè segmentation fault.
				shell->pipe = true;
			}
		}
		i++;
	}
	return (0);
}
