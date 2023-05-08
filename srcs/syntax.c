#include "../includes/minishell.h"

int ft_quotes_checksyntax(char *str)
{
    int i;
    int single_quotes;
    int double_quotes;
    
    i = 0;
    single_quotes = 0;
    double_quotes = 0;
    while (str[i])
    {
        if (str[i] == 39)
            single_quotes++;
        else if (str[i] == 34)
            double_quotes++;
        i++;
    }
    if ((single_quotes % 2) != 0 || (double_quotes % 2) != 0)
        return (1);
    else
        return (0);
}

int ft_op_checksyntax(char *str)
{
    // int i;

    // i = 0;

    if (check_syntax(str))
        return (1);
    // while (str[i])
    // {

    //     //! DA FIXARE I CONTROLLI SU AND
    //     if (str[i] == 124)
    //     {
    //         if(str[i+1] == 124 && (str[i+2]  == 124))
    //             printf("troppi or\n");
    //         else
    //             printf("ok or\n");
    //     }
    //     if (str[i] == 38 && str[i+1] == 38 && (str[i + 2] != 38))
    //     {
    //         printf("%c", str[i]);
    //         printf("ok and\n");
    //     }
    //     else
    //     {
    //         printf("troppi and\n"); 
    //         break ;
    //     }
    //     i++;
    // }
    // if ((or < 2) != 0 || (and % 2) != 0)
        // return (1);
    // else
        return (0);
}
