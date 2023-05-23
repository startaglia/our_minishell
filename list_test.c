/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: startagl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:22:39 by startagl          #+#    #+#             */
/*   Updated: 2023/05/15 16:30:02 by startagl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <curses.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h> 

typedef struct s_main
{
	struct s_node	*token;
}	t_main;

typedef struct s_node
{
	char			*command;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;


t_node *ft_lstnew(void *content, t_main *main)
{
	t_node	*nlist;

	nlist = (t_node *)malloc(sizeof(t_node));
	if (!nlist)
		return (NULL);
	nlist->command = strdup(content);
	return (nlist);
}

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*node;

	if (!lst || !new)
		return ;
	node = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new;
	new->prev = node;
}

int main(int argc, char **argv)
{
	(void)argc;
	int i = 0;
	t_main *main;

	main = (t_main *) malloc(sizeof(t_main));
	main->token = (t_node *) malloc(sizeof(t_node));
	main->token = ft_lstnew((char *)argv[0], main);
	printf("\n\ncontent-->%s\n", main->token->command);
	while(i < 5)
	{
		ft_lstadd_back(&main->token, ft_lstnew((char *)argv[++i], main));		
		main->token = main->token->next;
		printf("ind: %i content--> %s\n", i, main->token->command);
	}
	i = 5;
	while (main->token)
	{
		printf("ind: %i content_rev--> %s\n", i, main->token->command);
		main->token = main->token->prev;
		i--;
	}
}