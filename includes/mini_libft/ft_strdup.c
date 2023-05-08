#include "../minishell.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;
	int		size;

	size = 0;
	while (src[size])
		size++;
	dup = malloc(sizeof(*dup) * (size + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (src[++i])
		dup[i] = src[i];
	dup[i] = '\0';
	return (dup);
}
