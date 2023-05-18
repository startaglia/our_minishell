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
# include "macros.h"
# include "libft/libft.h"

typedef struct s_shell	t_shell;
typedef struct s_node	t_node;


typedef	struct operators
{
	bool	or;
	bool	and;
	bool	pipe;
	bool	in;
	bool	out;
	bool	append;
	bool	heredoc;

} t_operators;

struct s_node
{
	t_operators		*operators;
	t_shell 		*shell;
	t_node			*next;
	t_node			*prev;
	char			*command;
};

struct s_shell
{
	char			*prompt;
	char			*test;
	char			*pipeline;
	char			*line_to_split;
	char			**pipe_words;
	char			**copy_env;
	bool			pipe;
	t_node			*node;
};

// Errors
int				std_error(char *error);
// void			print_error(int error);

// // mini_libft
// int				ft_strlen(const char *str);
// char			**ft_split(const char *s, char c);
// char			*ft_strdup(char *src);
// char			*ft_strjoin(const char *s1, const char *s2);
// int				ft_strncmp(const char *s1, const char *s2, unsigned int n);

// readline
extern	void	rl_replace_line(const char *text, int clear_undo);

//init_functs
int				init_values(t_shell *shell, char **env);

// reader
int				init_prompt(t_shell *shell, char **env);

// syntax
int				check_syntax(t_shell *shell);
int				check_quotes(char *str);
int				check_in(char *str);
int				check_out(char *str);
int				check_pipes(t_shell *shell);

//parser
char			*parsing(t_shell *shell);
void			create_instruction_list(t_shell *shell);

//executor
int				exec_single_cmd(t_shell *shell);
int				ft_checkbuiltin(char *command);
int				ft_exec_builtin(char **cmd);
int				ft_cd(char **command);
int				ft_echo(char **command);
int				ft_pwd(void);

//free
int				free_matrix(char **matrix);


# endif