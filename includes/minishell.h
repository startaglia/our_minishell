/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:23 by scastagn          #+#    #+#             */
/*   Updated: 2023/05/26 21:43:24 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "macros.h"
# include "libft/libft.h"



typedef struct s_shell
{
	char	*prompt;
	char	*pipeline;
	char	*line_to_split;
	char	**pipe_words;
	char	**copy_env;
}	t_shell;

typedef struct s_node
{
	t_shell *shell;
}	t_node;

// Errors
int				std_error(char *error);

// readline
extern	void	rl_replace_line(const char *text, int clear_undo);

// reader
void 			init_prompt(t_shell *shell, char **envp);
int				init_values(t_shell *shell);

// syntax
int				check_syntax(char *str);
int				check_quotes(char *str);
int				check_in(char *str);
int				check_out(char *str);
int				check_pipes(char *str);

// parser
char			*parsing(t_shell *shell);

//executor
int				executor(t_shell *shell);

//free
int				free_matrix(char **matrix);
void			ft_free_shell(t_shell *shell);


# endif