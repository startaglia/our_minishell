/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:01:18 by startagl          #+#    #+#             */
/*   Updated: 2023/05/08 17:11:47 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 60)
		{
			i++;
			if (str[i] == 60)
			{
				i++;
				if (str[i] == 60)
					break ;
			}
		}
		i++;
	}
	return (0);
}

int	check_out(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 62)
		{
			i++;
			if (str[i] == 62)
			{
				i++;
				if (str[i] == 62)
					break ;
			}
		}
		i++;
	}
	return (0);
}