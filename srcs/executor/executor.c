/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:30:52 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/04 18:30:39 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_findpath(char *cmd)
{
    char *path;
    //* QUESTA E' LA PATH CORRETTA DELL'ESEGUIBILE, SE VIENE TROVATO
    char *right_path;
    //*QUESTA 'E MATRIX DELLA SPLIT FATTA SU PATH CON I :
    char **paths;
    int i;

    i = 0;
    path = getenv("PATH");
    paths = ft_split(path, ':');
    while(paths[i])
    {
        //*MI SERVE CREARE UNA STRINGA CHE ABBIA OGNI DIRECTORY CHE ERA NELLA VAR DI AMBIENTE PATH SEPARATA DAI : CON AGGIUNTO ALLA FINE /, PERCHE' SUBITO DOPO ANDRO' A CONTROLLARE SE IL COMMAND INSERITO HA GLI ACCESSI E QUINDI SE ESISTE. IN SOSTANZA CICLO SU OGNI DIRECTORY DEGLI ESEGUIBILI BIM E CONTROLLO SE IL COMANDO CHE HO SCRITTO E' UNO DI LORO.
        path = ft_strjoin(paths[i], "/");
        //* ALLA FINE DELLA PATH DEL MOMENTO, DOPO AVERCI MESSO IL / CI METTO ANCHE IL COMANDO CHE HO SCRITTO, SE LA DIR ESISTE CI ENTRA CON ACCESS E MI RITORNO LA PATH CHE CERCAVO.
        right_path = ft_strjoin(path, cmd);
        free(path);
        if (access(right_path, F_OK) == 0)
        {
            free_matrix(paths);
            return (right_path);
        }
        free(right_path);
        i++;
    }
    free_matrix(paths);
    return (NULL);
}

int	error(char *str, char *err)
{
	while (*str)
		write(2, str++, 1);
	if (err)
		while (*err)
			write(2, err++, 1);
	write(2, "\n", 1);
	return (1);
}

int	exec(char **args, int len, int fd, char **env)
{
    char *bin_path;
    
	args[len] = NULL;
	dup2(fd, 0);
	close(fd);
    bin_path = ft_findpath(args[0]);
	execve(bin_path, args, env);
    free(bin_path);
	return (error("error: cannot execute ", args[0]));
}

int executor(t_shell *shell)
{
	int	i;
	int	pid;
	int	tmp;
	int	fd[2];

	i = 0;
	pid = 0;
	tmp = dup(0);
	while (shell->pipe_words[i])
	{
		if (i != 0)
			shell->pipe_words = &shell->pipe_words[i + 1];
		i = 0;
		while (shell->pipe_words[i] && strcmp(shell->pipe_words[i], "|"))
			i++;
		if (i != 0 && shell->pipe_words[i] == NULL)
		{
			pid = fork();
			if (!pid)
			{
				if (exec(shell->pipe_words, i, tmp, shell->copy_env))
					return (1);
			}
			else
			{
				close(tmp);
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					;
				tmp = dup(0);
			}
		}
		else if (i != 0 && !strcmp(shell->pipe_words[i], "|"))
		{
			pipe(fd);
			pid = fork();
			if (!pid)
			{
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
				if (exec(shell->pipe_words, i, tmp, shell->copy_env))
					return (1);
			}
			else
			{
				close(tmp);
				close(fd[1]);
				tmp = fd[0];
			}
		}
	}
	close(tmp);
	return (0);
}