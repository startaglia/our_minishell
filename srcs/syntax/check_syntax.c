/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:58:36 by startagl          #+#    #+#             */
/*   Updated: 2023/05/26 20:57:56 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_syntax(char *str)
{
    if (check_quotes(str))
        return (1);
    if (check_in(str))
        return (1);
    if (check_out(str))
        return (1);
    if (check_pipes(str))
        return (1);
    return (0);
}