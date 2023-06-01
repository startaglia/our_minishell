/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:35:59 by startagl          #+#    #+#             */
/*   Updated: 2023/06/01 14:24:28 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34 && str[i + 1])
				i++;
		}
		if (str[i] == 124)
		{
			i++;
			if (str[i] == 124)
			{
				i++;
				if (str[i] == 124)
					return (std_error(PIP));
			}
		}
		i++;
	}
	return (0);
}
