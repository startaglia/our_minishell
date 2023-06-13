/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:47 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/08 21:13:56 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void handle_siginit(int sig)
{
    if (sig == SIGINT)
    {
        ioctl(STDIN_FILENO, TIOCSTI, "\n");
        rl_replace_line("", 0);
        rl_on_new_line();
    }
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void    ft_setenv(t_shell *shell, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    shell->copy_env = malloc (sizeof(char *) * (i + 1));
    i = 0;
    while (envp[i])
    {
        shell->copy_env[i] = ft_strdup(envp[i]);
        i++;
    }
    shell->copy_env[i] = NULL;
}

static void main_loop(t_shell *shell)
{
    t_list  *start;
    char    *expand_var;
    char    *expand_value;

    while (1)
    {
        signal(SIGINT, handle_siginit);
        signal(SIGQUIT, handle_sigquit);
        shell->pipeline = readline(shell->prompt);
        if (!shell->pipeline)
            break ;
        if (check_syntax(shell->pipeline))
        {
            free(shell->pipeline);
            continue ;
        }
        shell->line_to_split = parsing(shell);
        if (ft_strncmp(shell->pipeline, "", 1))
        {
            // int i = -1;
            add_history(shell->pipeline);
            if (shell->line_to_split == NULL)
                break ;
            expand_var = filter_expand(shell);
            expand_value = get_var_value(shell, expand_var);
            printf("expand value = %s\n", shell->expand_value);
            
            shell->pipe_words = ft_split_pipes(shell->line_to_split, 124);
            // while(shell->pipe_words[++i])
                // printf("VALUE--> %s\n", shell->pipe_words[i]);
            ///filter_expand;

            shell->cmds = ft_add_pipes(shell->pipe_words);
            create_cmd_list(shell);
            start = shell->cmds_list;
            executorprova(shell);
            ft_free_list(start);
            ft_free_execve(shell);
        }
        ft_free_shell(shell);
    }
}

char    *filter_expand(t_shell *shell)
{
    int     i;
    int     j;
    char    *str;
    
    i = 0;
    j = 0;
    while (shell->line_to_split[i])
    {
        j = 0;
        if (shell->line_to_split[i] == '$')
        {
            i++;
            while(shell->line_to_split[i] && shell->line_to_split[i] != 32)
            {
                //allocare
                //str[j] = shell->pipe_words[i];
                i++;
                j++;
            }
            str = malloc(sizeof(char) * (j + 1));
            i = i - j;
            j = 0;
            while(shell->line_to_split[i] && shell->line_to_split[i] != 32)
            {
                //allocare
                //printf("trovato $, %d, line to_split = %c\n", j, shell->line_to_split[i]);
                str[j] = shell->line_to_split[i];
                i++;
                j++;
            }
            str[j] = '\0';
            
        }
        i++;
    }
    // printf("str = %s, i = %d, j = %d\n", str, i, j);
    return(str);
}

char    *get_var_value(t_shell *shell, char   *var)
{
    int     i;
    int     j;
    char    *str = NULL;

    (void)str;
    i = 0;
    j = 0;
    while(shell->copy_env[i])
    {
        if (!strncmp (shell->copy_env[i], var, ft_strlen(var)))
        {
            shell->expand_value = strdup(trim_def(shell->copy_env[i]));
            // printf("var = %s\n", (shell->expand_value));
        }
        i++;
    }
    return(str);
}



void init_prompt(t_shell *shell, char **envp)
{
    char    *user;

    user = getenv("USER");
    if (!user)
        user = "guest";
    init_values(&shell);
    shell->prompt = ft_strjoin(user, "@minishell$ ");
    ft_setenv(shell, envp);
    main_loop(shell);
    free(shell->prompt);
    free_matrix(shell->copy_env);
    free(shell);
}