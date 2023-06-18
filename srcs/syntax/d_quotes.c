/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:59:54 by startagl          #+#    #+#             */
/*   Updated: 2023/05/10 12:59:49 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == 34)
			j++;
		else if (str[i] == 39)
			k++;
		i++;
	}
	if (j % 2 == 0 && k % 2 == 0)
		return (0);
	else if (j % 2 != 0)
		return (std_error(DUB_QUOT));
	else
		return (std_error(SIN_QUOT));
}
