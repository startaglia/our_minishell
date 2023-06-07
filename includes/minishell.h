/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:23 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/07 12:32:46 by dcarassi         ###   ########.fr       */
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


typedef struct s_command
{
	char				*cmd;
	char				**split_cmd;
	int					infile;
	int					outfile;
	int					copy_stdout;
	int					copy_stdin;
	char				*heredoc;
	struct t_command	*next;
}	t_command;

typedef struct s_shell
{
	char				*prompt;
	char				*pipeline;
	char				*line_to_split;
	char				**pipe_words;
	char				**cmds;
	char				**copy_env;
	struct s_list		*cmds_list;
}	t_shell;

// Errors
int				std_error(char *error);

// readline
extern	void	rl_replace_line(const char *text, int clear_undo);

// reader
void 			init_prompt(t_shell *shell, char **envp);
int				init_values(t_shell **shell);

// syntax
int				check_syntax(char *str);
int				check_quotes(char *str);
int				check_in(char *str);
int				check_out(char *str);
int				check_pipes(char *str);

// parser
char			*parsing(t_shell *shell);
char			**ft_split_pipes(char const *s, char c);
char			**ft_add_pipes(char **pipe_words);
void			create_cmd_list(t_shell *shell);
void			ft_set_redirs(t_shell *shell);
char			**ft_get_cmd(char **args);
char			*ft_find_heredoc(char **cmd);

//executor
int				executor(t_shell *shell);
int				executorprova(t_shell *shell);

//builtins
void			ft_echo(char **args);
void			ft_pwd();
void			ft_cd(char **args);
int				ft_is_builtin(char *cmd);
void			ft_exit();

//free
int				free_matrix(char **matrix);
void			ft_free_shell(t_shell *shell);
void			ft_free_list(t_list *list);


# endif