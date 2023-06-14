# include "../includes/minishell.h"

static void    ft_line_to_split_expand(t_shell *shell)
{
    int i;
    int j;
    int k;
    int g;

    i = 0; // contatore di line to split
    j = 0; // contatore di line to split expand
    k = 0; // contatore di expand_value
    g = 0; // contatore di exp_values
    while(shell->line_to_split[i])
    {
        if (shell->line_to_split[i] == '$')
        {
            i++;
            while(shell->line_to_split[i] && shell->line_to_split[i] != ' ')
                i++;
            while(shell->exp_values[g][k])
            {
                shell->line_to_split_expand[j] = shell->exp_values[g][k];
                j++;
                k++;
            }
            g++;
            k = 0;
        }
        if (shell->line_to_split[i])
        {
            shell->line_to_split_expand[j] = shell->line_to_split[i];
            i++;
            j++;
        }
    }
    shell->line_to_split_expand[j] = '\0';
}

static void  count_exp_vars(t_shell *shell)
{
    int i; // contatore line to split
    int cont; // n parole che iniziano col $

    i = 0;
    cont = 0;
    while (shell->line_to_split[i])
    {
        if (shell->line_to_split[i] == '$')
        {
            i++;
            cont++;
            while (shell->line_to_split[i] && shell->line_to_split[i] != ' ')
                i++;
        }
        else
            i++;
    }
    shell->n_exp_values = cont;    
    shell->exp_vars = malloc(sizeof(char *) * cont + 1);
    shell->exp_values = malloc(sizeof(char *) * cont + 1);
}

static int    filter_expand(t_shell *shell)
{
    int     i;
    int     j;
    int     f;
    int     g;

    i = 0; // contatore di line to split
    j = 0; // contatore di expand var
    f = 0; // valore di ritorno
    g = 0; // contatore di exp_vars
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
            shell->exp_vars[g] = malloc(sizeof(char) * (j + 1));
            i = i - j;
            j = 0;
            while(shell->line_to_split[i] && shell->line_to_split[i] != 32)
            {
                shell->exp_vars[g][j] = shell->line_to_split[i];
                i++;
                j++;
            }
            shell->exp_vars[g][j] = '\0';
            g++;
        }
        else
            i++;
    }
    shell->exp_vars[g] = NULL;
    return (f);
}

static int    get_var_values(t_shell *shell)
{
    int     i; // contatore strcmp opy_env
    int     ret; // ritorno
    char    *temp; // temporanea trim_def
    int     g; // contatore strcmp exp vars 

    i = 0;
    ret = 0;
    g = 0;
    temp = NULL;
    // if (!shell->exp_vars)
        // return (ret);
    // if (shell->exp_vars[g][0] == '?')
    // {
    //     shell->exp_values[g] = ft_itoa(exit_status);
    //     g++;
    //     return (1);
    // }
    while (g < shell->n_exp_values)
    {
        if (shell->exp_vars[g][0] == '?')
        {
            ret = 1;
            shell->exp_values[g] = ft_itoa(exit_status);
            g++;
            continue ;
        }
        else
        {
            while(shell->copy_env[i])
            {
                temp = trim_def(shell->copy_env[i]);
                if (!strncmp(shell->copy_env[i], shell->exp_vars[g], strlen(shell->exp_vars[g])))
                {
                    ret = 1;
                    // temp = trim_def(shell->copy_env[i]);
                    shell->exp_values[g] = strdup(temp);
                    free(temp);
                    break ;
                    // g++;
                }
                free(temp);
                i++;
            }
            if (i == 51 + shell->n_local_vars)
            {
                ret = 1;
                shell->exp_values[g] = strdup("");
            }
        }
        i = 0;
        g++;
    }
    // printf("#env[i]: %d\n", i);
    shell->exp_values[g] = 0;
    return (ret);
}

static int  get_exp_line_length(t_shell *shell)
{
    int ret; // valore di ritorno
    int i;  // per ciclare sulle matrici

    i = 0;
    ret = ft_strlen(shell->line_to_split);
    while (i < shell->n_exp_values)
    {
        ret = ret + ft_strlen(shell->exp_values[i]);
        i++;
    }
    i = 0;
    while (i < shell->n_exp_values)
    {
        ret = ret - ft_strlen(shell->exp_vars[i]);
        ret--;
        i++;
    }
    return (ret);
}

int    expander(t_shell *shell)
{
    int exp_line_length; // lunghezza della linea espansia
    size_t i;

    exp_line_length = 0;
    shell->line_to_split_expand = NULL;
    count_exp_vars(shell);
    if (filter_expand(shell))
    {
        if (get_var_values(shell))
        {
            exp_line_length = get_exp_line_length(shell);
            shell->line_to_split_expand = malloc(sizeof(char) * (exp_line_length + 1));
            // free(shell->expand_var);
            free_matrix(shell->exp_vars);
            ft_line_to_split_expand(shell);
            free_matrix(shell->exp_values);
        }
    }
    if (shell->line_to_split_expand != NULL)
    {
        i = 0;
        while(shell->line_to_split_expand[i] == 32)
            i++;
        if (i == ft_strlen(shell->line_to_split_expand))
            {
                free(shell->line_to_split_expand);
                shell->line_to_split_expand = strdup("");
                return (0);
            }
    }
    return (1);
}