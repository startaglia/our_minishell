#include "minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return ;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void free_nodes(t_node *node)
{
    t_node  *temp;

    while (node->next)
    {
        temp = node;
        node = node->next;
        free(temp);
    }
}
