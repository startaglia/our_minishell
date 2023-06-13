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
        // printf("%s\n", shell->copy_env[i]);
        i++;
    }
    shell->copy_env[i] = NULL;
}

void    line_to_split_expand(t_shell *shell)
{
    int i;
    int j;
    int k;

    i = 0; // contatore di line to split
    j = 0; // contatore di line to split expand
    k = 0; // contatore di expand_value
    while(shell->line_to_split[i])
    {
        shell->line_to_split_expand[j] = shell->line_to_split[i];
        if (shell->line_to_split[i] == '$')
        {
            i++;
            while(shell->expand_value[k])
            {
                shell->line_to_split_expand[j] = shell->expand_value[k];
                j++;
                k++;
            }
            i = i + ft_strlen(shell->expand_var) + 1;
            j++;
            k = 0;
        }
        i++;
        j++;
    }
}

static void main_loop(t_shell *shell)
{
    t_list  *start;

    while (1)
    {
        shell->expand_var = NULL;
        shell->expand_value = NULL;
        shell->line_to_split_expand = NULL;

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
        if (filter_expand(shell))
        {
            if (get_var_values(shell))
            {
                shell->line_to_split_expand = malloc(sizeof(char) * (ft_strlen(shell->expand_value) + ft_strlen(shell->line_to_split) + 1));
                line_to_split_expand(shell);
            }

        }
        if (ft_strncmp(shell->pipeline, "", 1))
        {
            // int i = -1;
            add_history(shell->pipeline);
            if (shell->line_to_split == NULL)
                break ;
            // shell->expand_value = NULL;
            // shell->expand_var = NULL;

            // printf("\tLINE_TO_SPLIT = %s\n", shell->line_to_split);
            // printf("\tLINE_TO_SPLIT_EXPAND = %s\n", shell->line_to_split_expand);
            // printf("expand value = %s\n", shell->expand_value);

            if (shell->line_to_split_expand != NULL)
                shell->pipe_words = ft_split_pipes(shell->line_to_split_expand, 124);
            else
                shell->pipe_words = ft_split_pipes(shell->line_to_split, 124);
            // while(shell->pipe_words[++i])
                // printf("VALUE--> %s\n", shell->pipe_words[i]);
            ///filter_expand;

            shell->cmds = ft_add_pipes(shell->pipe_words);
            create_cmd_list(shell);
            start = shell->cmds_list;
            executorprova(shell);
            free(shell->expand_var);
            free(shell->expand_value);
            ft_free_list(start);
            ft_free_execve(shell);
        }
        ft_free_shell(shell);
    }
}

int    filter_expand(t_shell *shell)
{
    int     i;
    int     j;
    int     f;

    i = 0;
    j = 0;
    while (shell->line_to_split[i])
    {
        j = 0;
        if (shell->line_to_split[i] == '$')
        {
            f = 1;
            i++;
            while(shell->line_to_split[i] && shell->line_to_split[i] != 32)
            {
                i++;
                j++;
            }
            shell->expand_var = malloc(sizeof(char) * (j + 1));
            i = i - j;
            j = 0;
            while(shell->line_to_split[i] && shell->line_to_split[i] != 32)
            {
                shell->expand_var[j] = shell->line_to_split[i];
                i++;
                j++;
            }
            shell->expand_var[j] = '\0';
        }
        i++;
    }
    return (f);
}

int    get_var_values(t_shell *shell)
{
    int     i;
    int     j;
    int     ret;

    i = 0;
    j = 0;
    ret = 0;
    // printf("XPANDVAR %s\n", shell->expand_var);
    while(shell->copy_env[i])
    {
        // printf("SHELL_COPY_ENV = %s\n", shell->copy_env[i]);

        if (!strncmp(shell->copy_env[i], shell->expand_var, strlen(shell->expand_var)))
        {
            // printf("VALORE = %s\n", shell->copy_env[i]);
            ret = 1;
            shell->expand_value = strdup(trim_def(shell->copy_env[i]));
        }
        // printf("VAR FUORI = %s\n", (shell->expand_value));

        i++;
    }
    return (ret);
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