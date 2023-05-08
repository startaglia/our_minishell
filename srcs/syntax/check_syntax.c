/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:58:36 by startagl          #+#    #+#             */
/*   Updated: 2023/05/08 12:52:03 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_syntax(char *str)
{
    if (check_quotes(str))
        return (1);
    // if (check_pipes(str))
    //     return (1);
    // if (check_and(str))
    //     return (1);
    // if (check_redirs(str))
    //     return (1);
    return (0);
}