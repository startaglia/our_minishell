/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:10:48 by dcarassi          #+#    #+#             */
/*   Updated: 2023/06/08 14:25:51 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments
// ◦ exit with no options

int ft_is_builtin(char *cmd)
{
	
    if (!strcmp(cmd, "echo"))
        return (1);
	else if (!strcmp(cmd, "cd"))
        return (2);
	else if (!strcmp(cmd, "pwd"))
        return (3);
	else if (!strcmp(cmd, "export"))
        return (4);
	else if (!strcmp(cmd, "unset"))
        return (5);
	else if (!strcmp(cmd, "env"))
       return (6);
	else if (!strcmp(cmd, "exit"))
        return (7);
	// else if (!strcmp(cmd, "^D"))
	// 	return (15);
	
    return (0);
}

void    ft_echo(char **args)
{
    int i;
    int newline;

    i = 1;
    if (!strcmp(args[1], "-n"))
    {
        newline = 1;
        i++;
    }
    else
        newline = 0;
    while (args[i])
    {
        printf("%s", args[i]);
        i++;
    }
    if (!newline)
            printf("\n");
}

void	ft_pwd(char **env)
{
	char	cwd[256];

	(void)env;
	char *path_history_prev = getcwd(cwd, sizeof(cwd));
	printf("%s", path_history_prev);
	printf ("\n");
}
//IMPLEMENTARE CD -
void ft_cd(char **args, t_shell *shell)
{
	char	*prev_path;
	char 	*path_history_prev;
	char	cwd[256];
	char 	*stringa;
	int		j;
	int		k;

	prev_path = NULL;
	path_history_prev = getcwd(cwd, sizeof(cwd));
	j = line_counter(shell->copy_env, "OLDPWD");
	k = line_counter(shell->copy_env, "PWD");
	printf("j = %d k = %d\n", j , k);
	if (!strcmp(args[1], "~"))
		chdir(getenv("HOME"));
	// if (!strcmp(args[1], "-"))
	// 	chdir();
	else if (!strcmp(args[1], "-"))
	{
		//copia path senza OLDPWD;
		//chdir(getenv("OLDPWD"));
		//chdir(exclude_var_name(shell->copy_env[k], "OLDPWD="));
		ft_pwd(shell->copy_env);
	}
	else
	{
		if (chdir(args[1]) != 0)
			printf("minishell: cd: %s: No such file or directory\n", args[1]);
		else
		{
			stringa = getcwd(cwd, sizeof(cwd));
			// printf("stringa = %s\n", stringa);
			// printf("shell->copy_env[10] = %s\n", shell->copy_env[10]);
			// printf("line_counter OLDPWD = %d\n", line_counter(shell->copy_env, "OLDPWD"));
			free(shell->copy_env[j]);
			shell->copy_env[j] = ft_strjoin("OLD", shell->copy_env[k]);
			free(shell->copy_env[k]);
			shell->copy_env[k] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
		}
	}
}

/*
//OBIETTIVO: COPIARE TESTO NELLA VARIABILE ENV, SENZA NOME VAR.
//dst = line - str
char	*exclude_var_name(char *line, char *str)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * ((ft_strlen(line) - ft_strlen(str)) + 1));
	i = ft_strlen(str);
	while (line[i])
		dst[j++] = line[i++];
	printf("dst= %s", dst);
	return(dst);
}*/

int	line_counter(char **copy_env, char *str)
{
	int		i;
	int		x;

	i = 0;
	x = ft_strlen(str);
	while(ft_strncmp(copy_env[i], str, x))
		i++;
	return(i);
}

//exit status
int ft_exit_status(int x)
{
	if (x == 1) 
		x = 127;
	printf("%d: command not found\n", x);
	return (x);
}

int	print_env(char **copy_env)
{	
	int		i;

	i = 0;
	while(copy_env[i]!= NULL)
	{
		printf("%s\n", copy_env[i]);
		i++;
	}
	return(0);
}

// void	ft_exit()
// {
// 	exit(0);
// }