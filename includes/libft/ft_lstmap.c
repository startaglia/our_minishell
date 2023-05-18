/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:29:26 by dcarassi          #+#    #+#             */
/*   Updated: 2023/01/22 22:36:00 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new_list;
// 	t_list	*tmp;

// 	if (lst == NULL)
// 		return (0);
// 	new_list = 0;
// 	while (lst)
// 	{
// 		tmp = ft_lstnew(f(lst->content));
// 		if (tmp == NULL)
// 		{
// 			ft_lstclear(&tmp, *del);
// 			return (0);
// 		}
// 		ft_lstadd_back(&new_list, tmp);
// 		lst = lst->next;
// 	}
// 	return (new_list);
// }
