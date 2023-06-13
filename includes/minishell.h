/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:23 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/11 16:15:52 by scastagn         ###   ########.fr       */
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
	char				*line_to_split_expand;
	char				**pipe_words;
	char				**cmds;
	char				**copy_env;
	char				*expand_var;
	char				*expand_value;
	struct s_list		*cmds_list;
}	t_shell;

extern int				exit_status;
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
char			*trim_def(char *full);
char			*getpath(char **env);
int				ft_findvar(t_shell *shell, t_command *cmd);
int				get_matrix_lenght(char **matrix);

//executor
int				executor(t_shell *shell);
int				executorprova(t_shell *shell);
int				ft_is_builtin(char *cmd);
void			ft_echo(char **args);
void			ft_pwd(char **env);
void			ft_env(char **env);
void			ft_cd(t_shell *shell, t_command *cmd);
void			update_cwd(t_shell *shell);
void			update_cwd_reverse(t_shell *shell);
void			ft_back_home(t_shell *shell);
void			ft_export(t_shell *shell, t_command *cmd);
int				ft_check_var(char **copy_env, t_command *cmd, int mode);
int				ft_changevalue(char **copy_env, t_command *cmd, int	i);
void			ft_unset(t_shell *shell, t_command *cmd);
void			ft_exit(t_shell *shell, t_list *start);

//expander
void    expander(t_shell *shell);

//free
int				free_matrix(char **matrix);
void			ft_free_shell(t_shell *shell);
void			ft_free_list(t_list *list);
void			ft_free_execve(t_shell *shell);


# endif