# include "../includes/minishell.h"

static void    ft_line_to_split_expand(t_shell *shell)
{
    int i;
    int j;
    int k;

    i = 0; // contatore di line to split
    j = 0; // contatore di line to split expand
    k = 0; // contatore di expand_value
    while(shell->line_to_split[i])
    {
        if (shell->line_to_split[i] == '$')
        {
            i++;
            while(shell->line_to_split[i] && shell->line_to_split[i] != ' ')
                i++;
            while(shell->expand_value[k])
            {
                shell->line_to_split_expand[j] = shell->expand_value[k];
                j++;
                k++;
            }
            k = 0;
        }
        else
        {
            shell->line_to_split_expand[j] = shell->line_to_split[i];
            i++;
            j++;
        }
    }
    shell->line_to_split_expand[j] = '\0';
}

static int    filter_expand(t_shell *shell)
{
    int     i;
    int     j;
    int     f;

    i = 0; // contatore di line to split
    j = 0; // contatore di expand var
    f = 0; // valore di ritorno
    while (shell->line_to_split[i])
    {
        j = 0;
        // if (shell->line_to_split[i] == 39)
        // {
        //     i++;
        //     while (shell->line_to_split[i] != 39)
        //         i++;
        // }
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
        else
            i++;
    }
    return (f);
}

static int    get_var_values(t_shell *shell)
{
    int     i;
    int     ret;
    char    *temp;

    i = 0;
    ret = 0;
    if (!shell->expand_var)
        return (ret);
    if (shell->expand_var[0] == '?')
    {
        shell->expand_value = ft_itoa(exit_status);
        return (1);
    }
    while(shell->copy_env[i])
    {
        if (!strncmp(shell->copy_env[i], shell->expand_var, strlen(shell->expand_var)))
        {
            ret = 1;
            temp = trim_def(shell->copy_env[i]);
            shell->expand_value = strdup(temp);
            free(temp);
        }
        i++;
    }
    return (ret);
}

void    expander(t_shell *shell)
{
    shell->line_to_split_expand = NULL;
    if (filter_expand(shell))
    {
        if (get_var_values(shell))
        {
            
            shell->line_to_split_expand = malloc(sizeof(char) * (ft_strlen(shell->line_to_split) - ft_strlen(shell->expand_var) + ft_strlen(shell->expand_value) + 1));
            free(shell->expand_var);
            ft_line_to_split_expand(shell);
            free(shell->expand_value);
        }
    }
}