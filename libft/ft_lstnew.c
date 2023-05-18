/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:51:30 by dcarassi          #+#    #+#             */
/*   Updated: 2023/05/16 12:47:40 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstnew(void *content)
{
	t_node	*new;

	new = (t_node *) malloc (sizeof(t_node));
	if (!new)
		return (NULL);
	new->command = ft_strdup(content);
	new->prev = NULL;
	return (new);
}
