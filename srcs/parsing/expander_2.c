#include "../includes/minishell.h"

char	*ft_strdupfrom(char const *s, int inizio, int fine)
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

char	*ft_findvalue(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name)))
			return (trim_def(env[i]));
		i++;
	}
	return (strdup(""));
}

int	ft_check_if_expanded(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' || line[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_home_dir(int *i, int *k, char *expa, t_shell *shell)
{
	char	*varvalue;

	if (shell->line_to_split[*i + 1] == 34 || !shell->line_to_split[*i + 1] || shell->line_to_split[*i + 1] != '~')
	{
		varvalue = ft_findvalue("HOME", shell->copy_env);
		expa = strcat(expa, varvalue);
		*k = ft_strlen(expa);
		(*i)++;
		free(varvalue);
	}
	return (expa);
}

char	*expand_exit_status(int *i, int *k, char *expanded)
{
	char	*varvalue;

	varvalue = ft_itoa(g_exit_status);
	expanded = strcat(expanded, varvalue);
	free(varvalue);
	(*i)++;
	(*k)++;
	return (expanded);
}
