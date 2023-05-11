# ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

// struct t_token;

typedef struct s_shell
{
	char	*prompt;
	char	*pipeline;
	char	**splitted_pipe;
	struct t_token	*tokens;
}	t_shell;

// Errori
void			print_error(int error);

// Readline
extern	void	rl_replace_line(const char *text, int clear_undo);

// Reader
void 			init_prompt(t_shell *shell);
int 			check_syntax(char *str);
int				check_redirs(char *str);
// void    split_readline(t_shell *shell);

# endif