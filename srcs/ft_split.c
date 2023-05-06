#include "minishell.h"

static int	word_count(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*malloc_word(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char **actual_split(const char *str, char c)
{
	int		i;
	int		j;
	int		index;
	char	**ret;

	ret = malloc((word_count(str, c) + 1) * sizeof(char *));
	if (!str || !ret)
		return (NULL);
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(str))
	{
		if (str[i] != c && index < 0)
			index = i;
		else if ((str[i] == c || i == ft_strlen(str)) && index >= 0)
		{
			ret[j++] = malloc_word(str, index, i);
			index = -1;
		}
	}
	ret[j] = 0;
	return (ret);
}

char	**ft_split(const char *str, char c)
{
	char	**ret;

	if (!str || !*str)
	{
		ret = malloc(sizeof(char *));
		if (!ret)
			return (NULL);
		return (ret);
	}
	return (actual_split(str, c));
}