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

typedef struct s_node
{
	char			*command;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_shell
{
	char			*prompt;
	char			*pipeline;
	char			*line_to_split;
	char			**splitted_pipe;
	char			**execve_arg;
	struct s_node	*token;
}	t_shell;

// Utils
int  			mat_len(char **mat);

// Free
void			ft_free_matrix(char **matrix);

// Errors
void			print_error(int error);
void 			write_std_error(char *error);

// Readline
extern	void	rl_replace_line(const char *text, int clear_undo);

// Reader
void			init_prompt(t_shell *shell, char **envp);
int 			check_syntax(char *str);
int				check_redirs(char *str);

// Parser
char			*parsing(t_shell *shell);
void		    create_instruction_list(t_shell *shell);

// Executor
char    		*get_path(char *cmd);

# endif