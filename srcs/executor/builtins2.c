/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:10:59 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/08 22:24:53 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    print_env_value(char *str, char **env)
{
    int     i;

    if (!str)
        return ;
    i = 0;
    while (env[i])
    {
        if (!ft_strncmp(str, env[i], ft_strlen(str)))
            printf("%s", env[i]);
        i++;
    }
    // printf("%s\n", ret[i]);
}

static int    ft_echo_dollar(char *str, char **env)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            if (str[i + 1])
                break;
            else
                return (0);
        }
        i++;
    }
    if (i == ft_strlen(str))
        return(0);
    else
    {
        str++;
        print_env_value(str, env);
        return (1);
    }
    return (0);
}

void    ft_echo(char **args, char **env)
{
    int i;
    int newline;

    if (!args[1])
    {
        printf("\n");
        return ;
    }
    i = 1;
    if (!strcmp(args[1], "-n"))
    {
        newline = 1;
        i++;
    }
    else
        newline = 0;
    if (ft_echo_dollar(args[i], env))
    {
        if (!newline)
            printf("\n");
        return ;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        i++;
    }
    if (!newline)
            printf("\n");
}