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
	// char	cwd[256];
	//int i;
	(void)env;
	// char *path_history_prev = getcwd(cwd, sizeof(cwd));
	// printf("%s", path_history_prev);
	// i = 4;
	// while(env[9][i])
	// {
	// 	write (1, &env[9][i], 1);
	// 	i++;
	// }
	printf ("\n");
}

// Nell'env di linux HOME=22, PWD=15, OLD_PWD=50
void ft_cd(char **args, t_shell *shell)
{	
	// char	*home;

	// (void)shell;
	// home = NULL;
	// printf("%s\n", getenv("HOME"));
	if (!args[1] || !strcmp(args[1], "~"))
	{
		// home = getenv("HOME");
		chdir(shell->copy_env[22]);
	}
	// else if (!strcmp(args[1], ".."))
	// 	chdir("..");
	else if (chdir(args[1]) == -1)
		printf("minishell: cd: %s: No such file or directory\n", args[1]);
}

// void	ft_exit()
// {
// 	exit(0);
// }

// FARE FUNZIONI CD, EXIT, PWD

// EXIT. NON BASTA EXIT(0), MA BISOGNA LIBERARE TUTTA LA MEMORIA ALLOCATA:
//1) MODIFICARE TUTTI I MALLOC SALVANDO TUTTI GLI INDIRIZZI DI MEMORIA IN UN ARRAY DI STRINGHE. E AGGIUNGENDO UN CONTATORE:
// ESEMPIO:
// char     *address_collector;
// int      i;
// char		*anything;
//
// address collector = malloc(sizeof(char) * number_of_allocated_stuff);
// 
// 