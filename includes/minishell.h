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



typedef struct s_shell
{
	char	*prompt;
	char	*pipeline;
	char	**pipe_words;
}	t_shell;

typedef struct s_node
{
	t_shell *shell;
}	t_node;

// Errors
void			print_error(int error);

// mini_libft
int				ft_strlen(const char *str);
char			**ft_split(const char *s, char c);
char			*ft_strdup(char *src);
char			*ft_strjoin(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);

// readline
extern	void	rl_replace_line(const char *text, int clear_undo);

// reader
void 			init_prompt(t_shell *shell);

// syntax
int				check_syntax(char *str);
int				check_quotes(char *str);
int				check_in(char *str);
int				check_out(char *str);
int				check_pipes(char *str);


# endif