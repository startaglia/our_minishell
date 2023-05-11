/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:57:08 by startagl          #+#    #+#             */
/*   Updated: 2023/05/11 12:05:12 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if(!matrix)
		return (1);
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (0);
}

// int	free_nodes(t_node *node)
// {
// 	if (!node)
// 		return (1);
// 	while (node)
// 	{
		
// 	}
	
// }