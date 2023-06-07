/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:02:32 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/24 10:05:29 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clone;

	if (*lst)
	{
		while (*lst)
		{
			clone = (*lst)-> next;
			ft_lstdelone(*lst, del);
			*lst = clone;
		}
	}
}
