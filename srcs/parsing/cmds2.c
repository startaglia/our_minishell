/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:40:11 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/11 12:02:19 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_find_heredoc(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!strcmp(cmd[i], "<<"))
		{
			if (cmd[i + 1])
				return (cmd[i + 1]);
			i++;
		}
		i++;
	}
	return (NULL);
}
