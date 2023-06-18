/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:01:18 by startagl          #+#    #+#             */
/*   Updated: 2023/05/26 21:01:30 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_quoted_content(char *str, int i)
{
	if (str[i])
	{
		if (str[i] == 34)
		{
			i++;
			while (str[i + 1] && str[i] != 34)
				i++;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i + 1] && str[i != 39])
				i++;
		}
	}
	return (i);
}

int	check_in(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i = skip_quoted_content(str, i);
		if (str[i] == 60)
		{
			i++;
			if (str[i] == 60)
			{
				i++;
				if (str[i] == 60)
					return (std_error(IN));
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
		i = skip_quoted_content(str, i);
		if (str[i] == 62)
		{
			i++;
			if (str[i] == 62)
			{
				i++;
				if (str[i] == 62)
					return (std_error(OUT));
			}
		}
		i++;
	}
	return (0);
}
