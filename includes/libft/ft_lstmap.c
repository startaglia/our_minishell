/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:08:01 by scastagn          #+#    #+#             */
/*   Updated: 2023/01/24 10:09:46 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*newlist;

	if (!f || !lst)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		newnode = ft_lstnew(f(lst -> content));
		if (!newnode)
		{
			ft_lstclear(&newlist, (*del));
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		lst = lst -> next;
	}
	return (newlist);
}
