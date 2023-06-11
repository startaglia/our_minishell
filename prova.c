#include "includes/minishell.h"

size_t ft_strlen(const char *str)
{
    int i;

    if (!str)
        return(0);
    while(str[i])
        i++;
    return(i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != 0 || s2[i] != 0) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

char    *ft_expand_env(char *src, char **env)
{
    int     i;
    int     j;
    char    *ret;

    if (!src)
        return(NULL);
    i = 0;
    j = 0;
    ret = NULL;
    src++;
    printf("%s\n", src);
    while (env[i])
    {
        if (!ft_strncmp(src, env[i], ft_strlen(src)))
            ret = env[i] + ft_strlen(src) + 1;
        i++;
    }
    return (ret);
}

int main(int argc, char **argv, char **envp)
{

    char    *old_val = malloc(sizeof(char) * 4);
    old_val = "$PWD";
    char    *new_val;
    (void)argc;
    (void)argv;
    char    *temp = old_val++;
    new_val = ft_expand_env(temp, envp);
    printf("%s\n", new_val);
    // free(old_val);
    return(0);
}