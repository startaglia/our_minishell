/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:06:15 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/24 10:07:42 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*clone;

	if (!lst)
		return ;
	clone = lst;
	while (clone != NULL)
	{
		(*f)(clone -> content);
		clone = clone -> next;
	}
}
