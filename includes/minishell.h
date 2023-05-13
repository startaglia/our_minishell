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
# include "macros.h"

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

};

struct s_shell
{
	char			*prompt;
	char			*test;
	char			*pipeline;
	char			**pipe_words;
	t_node			*node;
};

// Errors
int				std_error(char *error);
// void			print_error(int error);

// mini_libft
int				ft_strlen(const char *str);
char			**ft_split(const char *s, char c);
char			*ft_strdup(char *src);
char			*ft_strjoin(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);

// readline
extern	void	rl_replace_line(const char *text, int clear_undo);

//init_functs
int				init_values(t_shell *shell);

// reader
int				init_prompt(t_shell *shell);

// syntax
int				check_syntax(char *str);
int				check_quotes(char *str);
int				check_in(char *str);
int				check_out(char *str);
int				check_pipes(char *str);

//parser
char			*parsing(t_shell *shell);


# endif