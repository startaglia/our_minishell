/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:58:36 by startagl          #+#    #+#             */
/*   Updated: 2023/05/10 12:10:02 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_syntax(t_shell *shell)
{
    if (check_quotes(shell->pipeline))
        return (1);
    if (check_in(shell))
        return (1);
    if (check_out(shell))
        return (1);
    if (check_pipes(shell))
        return (1);
    // if (check_out(str))
        // return (1);
    // if (check_and(str))
        // return (1);
    // if (check_redirs(str))
        // return (1);
    return (0);
}