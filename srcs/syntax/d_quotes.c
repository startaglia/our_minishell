/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:59:54 by startagl          #+#    #+#             */
/*   Updated: 2023/05/08 12:53:51 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int  check_quotes(char *str)
{
    int i;
    int j;
    int k;

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
    else
        return (1);
}
