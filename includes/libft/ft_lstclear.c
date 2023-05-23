/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:18:03 by dcarassi          #+#    #+#             */
/*   Updated: 2023/01/22 22:24:04 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list	*tmp;

// 	if (lst)
// 	{
// 		while (*lst)
// 		{
// 			tmp = (*lst)->next;
// 			ft_lstdelone(*lst, del);
// 			*lst = tmp;
// 		}
// 		*lst = 0;
// 	}
// }
