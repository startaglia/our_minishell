#include "../includes/minishell.h"

static int	ft_countwords(char const *s, char c)
{
	int		k;
	int		trovato;
	int		nwords;

	k = 0;
	trovato = 0;
	nwords = 0;
	while (s[k] != 0)
	{
	    k = skip_quoted_content((char *)s, k);
		if (s[k] != c && trovato == 0)
		{
			nwords = nwords + 1;
			trovato = 1;
		}
		else if (s[k] == c)
			trovato = 0;
		k++;
	}
	return (nwords);
}

static char	*ft_ft_strdupfrom(char const *s, int inizio, int fine)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc (sizeof (char) * (fine - inizio + 1));
	while (inizio < fine)
	{
		newstr[i] = s[inizio];
		inizio++;
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}

static char	**ft_dosplit(char **strs, char c, char const *s)
{
	int	k;
	int	j;
	int	inizio;
	int	fine;

	k = 0;
	j = 0;
	while (s[j] != 0)
	{
		if (s[j] != c)
		{
			inizio = j;
			while (s[j] != c && s[j])
			{
				j = skip_quoted_content((char *)s, j);
        	    j++;
			}
			fine = j;
			strs[k++] = ft_ft_strdupfrom(s, inizio, fine);
		}
		else if (s[j] == c)
			j++;
	}
	strs[k] = 0;
	return (strs);
}

char	**ft_split_pipes(char const *s, char c)
{
	char	**strs;

	strs = malloc (sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!s || !strs)
		return (0);
	strs = ft_dosplit(strs, c, s);
	return (strs);
}