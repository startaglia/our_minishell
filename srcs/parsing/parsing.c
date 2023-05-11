/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:42:48 by startagl          #+#    #+#             */
/*   Updated: 2023/05/11 13:04:45 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//60(<) 62(>)
int		check_in_out_space(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == 60 || str[i] == 62)
		{
			if (str[i + 1] != 60 && str[i + 1] != 62)
				k++;
			else if (str[i - 1] != 60 && str[i - 1] != 62)
				k++;
		}
		i++;
	}
	return (k);
}

int	parsing(t_shell *shell)
{
	char	*str;
	int		i;
	int		j;
	int		space;

	i = 0;
	j = 0;
	space = check_in_out_space(shell->pipeline);
	//!DA CAPIRE BENE IL PERCHE *2 E +1;
	str = (char *)malloc(sizeof(char *) + ft_strlen(shell->pipeline) + (space * 2) + 1);
	if (!str)
		return (1);
	return (0);
}