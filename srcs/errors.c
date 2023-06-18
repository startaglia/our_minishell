/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scastagn <scastagn@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:41 by scastagn          #+#    #+#             */
/*   Updated: 2023/06/18 21:30:34 by scastagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	std_error(char *error)
{
	int	i;

	i = 0;
	while (error[i])
		i++;
	return (write(2, error, i));
}

int	error(char *str, char *err)
{
	char *temp = "\x1b[31m";
	while (*temp)
		write(2, temp++, 1);
	if (err)
		while (*err)
			write(2, err++, 1);
	while (*str)
		write(2, str++, 1);
	write(2, "\n", 1);
	exit(1);
	return (1);
}
