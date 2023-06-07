/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:10:48 by dcarassi          #+#    #+#             */
/*   Updated: 2023/06/07 12:38:54 by dcarassi         ###   ########.fr       */
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

void	ft_pwd()
{
	char	cwd[256];

	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;
	int				cond;

	cond = 1;
	i = 0;
	while (i < n)
	{
		if (src[i] != '\0' && cond == 1)
			dest[i] = src[i];
		else
			cond = 0;
		if (cond == 0)
			dest[i] = '\0';
		i++;
	}
	printf("%s\n", dest);
	return (dest);
}

//IMPLEMENTARE CD -
void ft_cd(char **args)
{
	// int		i;
	// char	*curr_path;
	char	*prev_path;
	char 	*path_history_prev;
	char	cwd[256];

	prev_path = NULL;
	path_history_prev = getcwd(cwd, sizeof(cwd));
	if (!strcmp(args[1], "~"))
		chdir(getenv("HOME"));
	else if (!strcmp(args[1], ".."))
	{
		chdir("..");
		// curr_path = getenv("PWD");
		// i = ft_strlen(curr_path);
		// printf("i vale : %d\n", i);
		// while (i >= 0)
		// {
		// 	printf("%d\n", i);
		// 	if (curr_path[i] == '/')
		// 	{
		// 		prev_path = ft_strncpy(prev_path, curr_path, i);
		// 		printf("%s\n", prev_path);
		// 		// chdir(prev_path);
		// 		break ;
		// 	}
		// 	i--;
		// }
	}
	else if (!strcmp(args[1], "-"))
	{
		chdir(path_history_prev);
		ft_pwd();
	}
	else if (!strcmp(args[1], "."))
		return ;
	else
	{
		//curr_path = getenv("PWD");
		if (chdir(args[1]) == -1)
			printf("Nn esiste la cattella\n");
	}

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