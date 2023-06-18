/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:37:44 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/17 12:38:56 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_quotes(char *line, int *i, int *k, char *expanded)
{
	(*i)++;
	while (line[*i] && line[*i] != 39)
	{
		expanded[*k] = line[*i];
		(*k)++;
		(*i)++;
	}
	if (line[*i] != '\0')
		(*i)++;
	expanded[*k] = '\0';
	return (expanded);
}

char	*expand_variable(int *i, int *k, char *expa, t_shell *shell)
{
	int		start;
	char	*varname;
	char	*varvalue;

	start = *i;
	while (ft_isalpha(shell->line_to_split[*i]) && shell->line_to_split[*i])
		(*i)++;
	varname = ft_strdupfrom(shell->line_to_split, start, *i);
	varvalue = ft_findvalue(varname, shell->copy_env);
	free (varname);
	if (!varvalue)
	{
		free(varvalue);
		return (expa);
	}
	expa = strcat(expa, varvalue);
	*k = ft_strlen(expa);
	free (varvalue);
	return (expa);
}

char	*expand_the_rest(int *i, int *k, char *expanded, char *line)
{
	if (line[*i] != '\0')
	{
		expanded[*k] = line[*i];
		(*i)++;
		(*k)++;
		expanded[*k] = '\0';
	}
	return (expanded);
}

void	loop_expander(char *expanded, int *i, int *k, t_shell *s)
{
	while (s->line_to_split[*i])
	{
		if (s->line_to_split[*i] == 39)
		{
			expanded = expand_quotes(s->line_to_split, i, k, expanded);
			continue ;
		}
		if (s->line_to_split[*i] == 36)
		{
			(*i)++;
			if (s->line_to_split[*i] == 63)
			{
				expand_exit_status(i, k, expanded);
				continue ;
			}
			expanded = expand_variable(i, k, expanded, s);
			continue ;
		}
		if (s->line_to_split[*i] == '~' && s->line_to_split[*i - 1] == ' ')
		{
			expanded = expand_home_dir(i, k, expanded, s);
			continue ;
		}
		expanded = expand_the_rest(i, k, expanded, s->line_to_split);
	}
}

char	*expander(char *line, t_shell *shell)
{
	char	*expanded;
	int		i;
	int		k;

	(void)line;
	i = 0;
	k = 0;
	if (!ft_check_if_expanded(line))
		return (ft_strdup(line));
	expanded = malloc(sizeof(char) * 1024);
	expanded[0] = '\0';
	loop_expander(expanded, &i, &k, shell);
	if (expanded[0] == '\0')
		return (ft_strdup(line));
	expanded[k] = '\0';
	return (expanded);
}
